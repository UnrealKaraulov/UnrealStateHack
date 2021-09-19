using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.IO;

namespace WindowsFormsApplication1
{
    public partial class UnrealForm : Form
    {
        private Syringe.Injector war3injector;
        private Process war3proc = Process.GetCurrentProcess( );
        private Process war3proc2 = Process.GetCurrentProcess( );
        private ProcessMemory war3mem = null;
        private bool war3meminitialized = false;
        private bool injected = false;
        private delegate void SetDotaInfoLocation ( int offset );
        private SetDotaInfoLocation SetDotaInfoLocationInst;   // Ensure it doesn't get garbage collected

        struct ReadDotaInfoStruct
        {
            public int hero;     // 4
            public int kills;      // 8
            public int deaths;        // 12
            public int assists;      // 16
            public int creeps;      // 20
            public int gold;        // 24
            public int towers;      // 28
            public int couriers;      // 32
            public int item1;    // 36
            public int item2;    // 40
            public int item3;    // 44 
            public int item4;    // 48
            public int item5;    // 52
            public int item6;    // 56
        }

        ReadDotaInfoStruct [ ] dotainfo = new ReadDotaInfoStruct [ 10 ];


        private void DotaInfoProcessing ( int offset )
        {
            if ( Process.GetProcessesByName( "war3" ).Length == 0 )
            {
                war3meminitialized = false;
                MessageBox.Show( "Не найден war3.exe процесс!" );
                return;
            }

            if ( war3meminitialized && war3proc2 != Process.GetProcessesByName( "war3" ) [ 0 ] )
            {
                war3proc2 = Process.GetProcessesByName( "war3" ) [ 0 ];
                war3mem = new ProcessMemory( war3proc2.Id );
                war3mem.StartProcess( );
            }



            if ( war3meminitialized )
            {
                for ( int i = 0 ; i < dotainfo.Length ; i++ )
                {
                    int startoffset = i * 56;
                    dotainfo [ i ].hero = war3mem.ReadInt( offset + startoffset );
                    dotainfo [ i ].kills = war3mem.ReadInt( offset + startoffset + 4 );
                    dotainfo [ i ].deaths = war3mem.ReadInt( offset + startoffset + 8 );
                    dotainfo [ i ].assists = war3mem.ReadInt( offset + startoffset + 12 );
                    dotainfo [ i ].creeps = war3mem.ReadInt( offset + startoffset + 16 );
                    dotainfo [ i ].gold = war3mem.ReadInt( offset + startoffset + 20 );
                    dotainfo [ i ].towers = war3mem.ReadInt( offset + startoffset + 24 );
                    dotainfo [ i ].couriers = war3mem.ReadInt( offset + startoffset + 28 );
                    dotainfo [ i ].item1 = war3mem.ReadInt( offset + startoffset + 32 );
                    dotainfo [ i ].item2 = war3mem.ReadInt( offset + startoffset + 36 );
                    dotainfo [ i ].item3 = war3mem.ReadInt( offset + startoffset + 40 );
                    dotainfo [ i ].item4 = war3mem.ReadInt( offset + startoffset + 44 );
                    dotainfo [ i ].item5 = war3mem.ReadInt( offset + startoffset + 48 );
                    dotainfo [ i ].item6 = war3mem.ReadInt( offset + startoffset + 52 );
                }

            }

        }

        [DllImport( "DotaInfoLocatedAt.dll" )]
        private static extern void InitLocator ( SetDotaInfoLocation fn );

        public UnrealForm ( )
        {
            InitializeComponent( );
            SetDotaInfoLocationInst = new SetDotaInfoLocation( DotaInfoProcessing );
            InitLocator( SetDotaInfoLocationInst );
            editbox.Parent = listView1;
            editbox.Hide( );
            editbox.LostFocus += new EventHandler( editbox_LostFocus );
        }

        struct ActionStruct
        {
            public int actionid;
            public int player1id;
            public int player2id;
            public int actiondata;
        }

        private void button1_Click ( object sender , EventArgs e )
        {

            if ( injected && Process.GetProcessesByName( "war3" ).Length == 0 )
            {
                injected = false;
            }

            if ( injected && Process.GetProcessesByName( "war3" ) [ 0 ] != war3proc )
            {
                injected = false;
            }


            if ( Process.GetProcessesByName( "war3" ).Length > 0 && !injected )
            {

                war3injector = new Syringe.Injector( Process.GetProcessesByName( "war3" ) [ 0 ] );
                war3injector.EjectOnDispose = false;
                war3injector.InjectLibrary( Directory.GetCurrentDirectory( ) + @"\DSH.dll" );
                injected = true;
                war3proc = Process.GetProcessesByName( "war3" ) [ 0 ];
            }
            else
            {
                MessageBox.Show( "war3 ненайден! \nперезапустите iccup лаунчер и игру." );
            }

            if ( injected )
            {
                ActionStruct SendData = new ActionStruct( );
                SendData.actionid = ActionID.SelectedIndex;
                SendData.player1id = Player1ID.SelectedIndex;
                SendData.player2id = Player2ID.SelectedIndex;
                try
                {
                    SendData.actiondata = int.Parse( InputData.Text );
                }
                catch
                {
                    if ( InputData.Text.Length == 4 )
                    {
                        byte [ ] input1 = Encoding.UTF8.GetBytes( InputData.Text );
                        byte [ ] output1 = new byte [ ] { input1 [ 0 ] , input1 [ 1 ] , input1 [ 2 ] , input1 [ 3 ] };
                        SendData.actiondata = BitConverter.ToInt32( output1 , 0 );
                    }
                    else
                        SendData.actiondata = 0;
                }

                war3injector.CallExport<ActionStruct>( "DSH.dll" , "Execute" , SendData );
            }

        }

        int GetIntFromString ( string stringstring,int type = 0 )
        {
            int retvalue = 0;

            if ( type == 1 )
            {
                try
                {
                    retvalue = int.Parse( stringstring );
                }
                catch
                {
                    if ( stringstring.Length == 4 )
                    {
                        byte [ ] intputstr1 = Encoding.UTF8.GetBytes( stringstring );
                        byte [ ] outint1 = new byte [ ] { intputstr1 [ 0 ] , intputstr1 [ 1 ] , intputstr1 [ 2 ] , intputstr1 [ 3 ] };
                        retvalue = BitConverter.ToInt32( outint1 , 0 );
                    }
                    else
                        retvalue = 0;
                }
            }
            else
            {
                try
                {
                    retvalue = int.Parse( stringstring );
                }
                catch
                {
                    retvalue = 0;
                }
            }

            return retvalue;
        }

        void MoveInfoToData ( )
        {
            for ( int i = 0 ; i < 10 ; i++ )
            {
                dotainfo [ i ].hero = GetIntFromString( listView1.Items [ i ].SubItems [ 1 ].Text ,1);
                dotainfo [ i ].kills = GetIntFromString( listView1.Items [ i ].SubItems [ 2 ].Text );
                dotainfo [ i ].deaths = GetIntFromString( listView1.Items [ i ].SubItems [ 3 ].Text );
                dotainfo [ i ].assists = GetIntFromString( listView1.Items [ i ].SubItems [ 4 ].Text );
                dotainfo [ i ].creeps = GetIntFromString( listView1.Items [ i ].SubItems [ 5 ].Text );
                dotainfo [ i ].gold = GetIntFromString( listView1.Items [ i ].SubItems [ 6 ].Text );
                dotainfo [ i ].towers = GetIntFromString( listView1.Items [ i ].SubItems [ 7 ].Text );
                dotainfo [ i ].couriers = GetIntFromString( listView1.Items [ i ].SubItems [ 8 ].Text );
                dotainfo [ i ].item1 = GetIntFromString( listView1.Items [ i ].SubItems [ 9 ].Text , 1 );
                dotainfo [ i ].item2 = GetIntFromString( listView1.Items [ i ].SubItems [ 10 ].Text , 1 );
                dotainfo [ i ].item3 = GetIntFromString( listView1.Items [ i ].SubItems [ 11 ].Text , 1 );
                dotainfo [ i ].item4 = GetIntFromString( listView1.Items [ i ].SubItems [ 12 ].Text , 1 );
                dotainfo [ i ].item5 = GetIntFromString( listView1.Items [ i ].SubItems [ 13 ].Text , 1 );
                dotainfo [ i ].item6 = GetIntFromString( listView1.Items [ i ].SubItems [ 14 ].Text , 1 );
            }


        }

        string hIntToString ( int intint )
        {
            string returnstring = string.Empty;
            if (intint == 0)
            {
                returnstring = "0";
            }
            else
            {
                returnstring = Encoding.UTF8.GetString( BitConverter.GetBytes( intint ) );
                if ( returnstring.Length != 4 )
                    returnstring = "0";
                else
                {
                    Regex r = new Regex(@"^[\w|\d]*$");
                    if ( r.IsMatch( returnstring ) )
                    {

                    }
                    else
                    {
                        returnstring = "0";
                    }
                }
            }

            return returnstring;
        }

        void MoveDataToInfo ( )
        {
            for ( int i = 0 ; i < 10 ; i++ )
            {

                listView1.Items [ i ].SubItems [ 1 ].Text = hIntToString( dotainfo [ i ].hero );
                listView1.Items [ i ].SubItems [ 2 ].Text = dotainfo [ i ].kills.ToString( );
                listView1.Items [ i ].SubItems [ 3 ].Text = dotainfo [ i ].deaths.ToString( );
                listView1.Items [ i ].SubItems [ 4 ].Text = dotainfo [ i ].assists.ToString( );
                listView1.Items [ i ].SubItems [ 5 ].Text = dotainfo [ i ].creeps.ToString( );
                listView1.Items [ i ].SubItems [ 6 ].Text = dotainfo [ i ].gold.ToString( );
                listView1.Items [ i ].SubItems [7 ].Text = dotainfo [ i ].towers.ToString( );
                listView1.Items [ i ].SubItems [ 8].Text = dotainfo [ i ].couriers.ToString( );
                listView1.Items [ i ].SubItems [ 9 ].Text = hIntToString( dotainfo [ i ].item1 );
                listView1.Items [ i ].SubItems [ 10 ].Text = hIntToString( dotainfo [ i ].item2 );
                listView1.Items [ i ].SubItems [ 11 ].Text = hIntToString( dotainfo [ i ].item3 );
                listView1.Items [ i ].SubItems [ 12 ].Text = hIntToString( dotainfo [ i ].item4 );
                listView1.Items [ i ].SubItems [ 13 ].Text = hIntToString( dotainfo [ i ].item5 );
                listView1.Items [ i ].SubItems [ 14 ].Text = hIntToString( dotainfo [ i ].item6 );

            }
        }

        private ListViewHitTestInfo hitinfo;
        private TextBox editbox = new TextBox( );
        void editbox_LostFocus ( object sender , EventArgs e )
        {
            hitinfo.SubItem.Text = editbox.Text;
            editbox.Hide( );
            MoveInfoToData( );
            MoveDataToInfo( );
        }

        private void listView1_MouseDoubleClick ( object sender , MouseEventArgs e )
        {
            hitinfo = listView1.HitTest( e.X , e.Y );
            editbox.Bounds = hitinfo.SubItem.Bounds;
            editbox.Text = hitinfo.SubItem.Text;
            editbox.Focus( );
            editbox.Show( );
        }

        private void UnrealForm_Load ( object sender , EventArgs e )
        {
            ListViewItem item1 = new ListViewItem( "item1" , 0 );
            item1.SubItems.Add( "" );
            item1.SubItems.Add( "0" );
            item1.SubItems.Add( "0" );
            item1.SubItems.Add( "0" );
            item1.SubItems.Add( "0" );
            item1.SubItems.Add( "0" );
            item1.SubItems.Add( "0" );
            item1.SubItems.Add( "0" );
            item1.SubItems.Add( "" );
            item1.SubItems.Add( "" );
            item1.SubItems.Add( "" );
            item1.SubItems.Add( "" );
            item1.SubItems.Add( "" );
            item1.SubItems.Add( "" );
            listView1.Items.Add( item1.Clone( ) as ListViewItem );
            listView1.Items.Add( item1.Clone( ) as ListViewItem );
            listView1.Items.Add( item1.Clone( ) as ListViewItem );
            listView1.Items.Add( item1.Clone( ) as ListViewItem );
            listView1.Items.Add( item1.Clone( ) as ListViewItem );
            listView1.Items.Add( item1.Clone( ) as ListViewItem );
            listView1.Items.Add( item1.Clone( ) as ListViewItem );
            listView1.Items.Add( item1.Clone( ) as ListViewItem );
            listView1.Items.Add( item1.Clone( ) as ListViewItem );
            listView1.Items.Add( item1.Clone( ) as ListViewItem );
            MoveDataToInfo( );
        }

    }
}
