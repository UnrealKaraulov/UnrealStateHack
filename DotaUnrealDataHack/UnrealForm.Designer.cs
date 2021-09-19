namespace WindowsFormsApplication1
{
    partial class UnrealForm
    {
        /// <summary>
        /// Требуется переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose ( bool disposing )
        {
            if ( disposing && ( components != null ) )
            {
                components.Dispose( );
            }
            base.Dispose( disposing );
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Обязательный метод для поддержки конструктора - не изменяйте
        /// содержимое данного метода при помощи редактора кода.
        /// </summary>
        private void InitializeComponent ( )
        {
            this.listView1 = new System.Windows.Forms.ListView();
            this.PLAYERID = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.HeroID = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.HeroKills = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Deaths = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Assistscount = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.CreepCount = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.GoldCount = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.TowerCount = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.CourierCount = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Item1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Item2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Item3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Item4 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Item5 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Item6 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.label1 = new System.Windows.Forms.Label();
            this.ActionID = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.Player1ID = new System.Windows.Forms.ComboBox();
            this.Player2ID = new System.Windows.Forms.ComboBox();
            this.button1 = new System.Windows.Forms.Button();
            this.InputData = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // listView1
            // 
            this.listView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.PLAYERID,
            this.HeroID,
            this.HeroKills,
            this.Deaths,
            this.Assistscount,
            this.CreepCount,
            this.GoldCount,
            this.TowerCount,
            this.CourierCount,
            this.Item1,
            this.Item2,
            this.Item3,
            this.Item4,
            this.Item5,
            this.Item6});
            this.listView1.FullRowSelect = true;
            this.listView1.Location = new System.Drawing.Point(1, 12);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(688, 285);
            this.listView1.TabIndex = 0;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.View = System.Windows.Forms.View.Details;
            this.listView1.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.listView1_MouseDoubleClick);
            // 
            // PLAYERID
            // 
            this.PLAYERID.Text = "ID";
            this.PLAYERID.Width = 0;
            // 
            // HeroID
            // 
            this.HeroID.Text = "HERO";
            this.HeroID.Width = 48;
            // 
            // HeroKills
            // 
            this.HeroKills.Text = "Kills";
            this.HeroKills.Width = 42;
            // 
            // Deaths
            // 
            this.Deaths.Text = "Deaths";
            this.Deaths.Width = 52;
            // 
            // Assistscount
            // 
            this.Assistscount.Text = "Assists";
            this.Assistscount.Width = 46;
            // 
            // CreepCount
            // 
            this.CreepCount.Text = "Creeps";
            this.CreepCount.Width = 46;
            // 
            // GoldCount
            // 
            this.GoldCount.Text = "Gold";
            this.GoldCount.Width = 44;
            // 
            // TowerCount
            // 
            this.TowerCount.Text = "Towers";
            this.TowerCount.Width = 50;
            // 
            // CourierCount
            // 
            this.CourierCount.Text = "Couriers";
            this.CourierCount.Width = 54;
            // 
            // Item1
            // 
            this.Item1.Text = "Item1";
            this.Item1.Width = 48;
            // 
            // Item2
            // 
            this.Item2.Text = "Item2";
            this.Item2.Width = 49;
            // 
            // Item3
            // 
            this.Item3.Text = "Item3";
            this.Item3.Width = 44;
            // 
            // Item4
            // 
            this.Item4.Text = "Item4";
            this.Item4.Width = 49;
            // 
            // Item5
            // 
            this.Item5.Text = "Item5";
            this.Item5.Width = 52;
            // 
            // Item6
            // 
            this.Item6.Text = "Item6";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(20, 311);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(40, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Action:";
            // 
            // ActionID
            // 
            this.ActionID.FormattingEnabled = true;
            this.ActionID.Items.AddRange(new object[] {
            "Kill hero(Убить игрока)",
            "Kill creep(Убить крипов)",
            "Deny creep(Добить крипов)",
            "Set Gold (Установить золото)",
            "Set item 1 Установить итем)",
            "Set item 2 (Установить итем)",
            "Set item 3 (Установить итем)",
            "Set item 4 (Установить итем)",
            "Set item 5 (Установить итем)",
            "Set item 6 (Установить итем)",
            "Up level to (Поднять lvl до )",
            "Up assists to (Поднять lvl до )",
            "Win team 1 (Победила 1 тима)",
            "Win team 2 (Победила 2 тима)",
            "Do bad!(Сделать что-то плохое)",
            "Set heroid(Установить героя)",
            "Destroy TOP team1",
            "Destroy MID team1",
            "Destroy BOT team1",
            "Destroy TOP team2",
            "Destroy MID team2",
            "Destroy BOT team2"});
            this.ActionID.Location = new System.Drawing.Point(66, 308);
            this.ActionID.Name = "ActionID";
            this.ActionID.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.ActionID.Size = new System.Drawing.Size(167, 21);
            this.ActionID.TabIndex = 2;
            this.ActionID.Text = "Kill hero(Убить героя)";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(319, 311);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(48, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Player 1:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(428, 311);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(48, 13);
            this.label3.TabIndex = 3;
            this.label3.Text = "Player 2:";
            // 
            // Player1ID
            // 
            this.Player1ID.FormattingEnabled = true;
            this.Player1ID.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10"});
            this.Player1ID.Location = new System.Drawing.Point(374, 308);
            this.Player1ID.Name = "Player1ID";
            this.Player1ID.Size = new System.Drawing.Size(48, 21);
            this.Player1ID.TabIndex = 4;
            this.Player1ID.Text = "1";
            // 
            // Player2ID
            // 
            this.Player2ID.FormattingEnabled = true;
            this.Player2ID.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10"});
            this.Player2ID.Location = new System.Drawing.Point(482, 308);
            this.Player2ID.Name = "Player2ID";
            this.Player2ID.Size = new System.Drawing.Size(48, 21);
            this.Player2ID.TabIndex = 4;
            this.Player2ID.Text = "1";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(549, 306);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(128, 23);
            this.button1.TabIndex = 5;
            this.button1.Text = "Выполнить! (Execute!)";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // InputData
            // 
            this.InputData.Location = new System.Drawing.Point(239, 308);
            this.InputData.Name = "InputData";
            this.InputData.Size = new System.Drawing.Size(79, 20);
            this.InputData.TabIndex = 6;
            // 
            // UnrealForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(689, 333);
            this.Controls.Add(this.InputData);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.Player2ID);
            this.Controls.Add(this.Player1ID);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.ActionID);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.listView1);
            this.Name = "UnrealForm";
            this.Text = "Dota Unreal State Hаck";
            this.Load += new System.EventHandler(this.UnrealForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.ColumnHeader PLAYERID;
        private System.Windows.Forms.ColumnHeader HeroID;
        private System.Windows.Forms.ColumnHeader CreepCount;
        private System.Windows.Forms.ColumnHeader GoldCount;
        private System.Windows.Forms.ColumnHeader TowerCount;
        private System.Windows.Forms.ColumnHeader Item1;
        private System.Windows.Forms.ColumnHeader Item2;
        private System.Windows.Forms.ColumnHeader Item3;
        private System.Windows.Forms.ColumnHeader Item4;
        private System.Windows.Forms.ColumnHeader Item5;
        private System.Windows.Forms.ColumnHeader Item6;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox ActionID;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox Player1ID;
        private System.Windows.Forms.ComboBox Player2ID;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox InputData;
        private System.Windows.Forms.ColumnHeader CourierCount;
        private System.Windows.Forms.ColumnHeader HeroKills;
        private System.Windows.Forms.ColumnHeader Deaths;
        private System.Windows.Forms.ColumnHeader Assistscount;
    }
}

