using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using CoreWrapper;


namespace Mastepiece
{
    public partial class MainWindow : Form
    {
        public MainWindow()
        {
            InitializeComponent();
            f = this.CreateGraphics();
            Sensor sensor = new Sensor(SensorType.TEMPERATURE_SENSOR, 0, 50, 2);
            controlModel = new ControlModel(sensor, 5);
            for (int i = 0; i < 16; i++) g[i] = new Label();
            Timer timer = new Timer();
            timer.Interval = 2000;
            timer.Tick += OnTimer;
            timer.Start();
        }

        public Label[] g = new Label[17];

        Graphics f;
        void DrawLayer(List<Granule> layer, int number)
        {

            int height_window = this.Height;
            int widght_window = this.Width;
            int start_X = 50;
            int start_Y = 100;

            f.DrawRectangle(Pens.Black, 50, 100, widght_window - 100, height_window - 150);
            f.DrawLine(Pens.Black, start_X + 50, ((height_window) / 2), widght_window - 150, ((height_window) / 2));
            int line_widght = widght_window - 150 - start_X - 50;
            int size_x = 0;
            if (line_widght % layer.Count > 5)
                size_x = line_widght / layer.Count + 1;
            else
                size_x = line_widght / layer.Count;
            int size_y = 30 * number;
            start_X = start_X + 50;
            Random r = new Random();
            Brush br;
            br = new SolidBrush(Color.FromArgb(r.Next(255), r.Next(255), r.Next(255), r.Next(255)));
            for (int i = 1; i < layer.Count + 1; i++)
            {
                br = new SolidBrush(Color.FromArgb(r.Next(255), r.Next(255), r.Next(255), r.Next(255)));
                f.FillRectangle(br, start_X, ((height_window) / 2), size_x, size_y + 20);
                start_X = start_X + size_x;

            }
            start_X = line_widght / layer.Count + 1;
            int start_lab = (height_window) / 2 + 5;
            int index = 0;
            if (number > 1)
            {
                start_lab = (height_window) / 2 + 50;
                index = 11;
            }


            foreach (Granule granule in layer)
            {

                g[index].Text = "";
                g[index].Location = new System.Drawing.Point(start_X + 50, start_lab);
                g[index].Text = granule.FuzzyFactor.ToString();
                g[index].BackColor = System.Drawing.Color.Transparent;
                if (g[index].Text.Length > 3)
                    g[index].Text.Substring(0, 3);
                g[index].Width = 40;
                start_X = start_X + size_x;
                this.Controls.AddRange(new Control[] { g[index] });
                index++;
            }

        }

        void OnTimer(Object sender, EventArgs e)
        {
            valueBox.Clear();
            controlModel.Update();
            valueBox.Text += "Layer 1: ";
            List<Granule> layer1 = controlModel.SensorMemory.GetGranules(0);


            foreach (Granule granule in layer1)
            {
                valueBox.Text += granule.FuzzyFactor + " ";
            }

            valueBox.Text += "\r\n\r\nLayer 2: ";
            if (controlModel.SensorMemory.LayerCount >= 2)
            {
                controlModel.SensorMemory.RemoveTopLayer();
            }
            controlModel.SensorMemory.AddLayer(2);
            List<Granule> layer2 = controlModel.SensorMemory.GetGranules(1);
            foreach (Granule granule in layer2)
            {
                valueBox.Text += granule.FuzzyFactor + " ";
            }
            DrawLayer(layer2, 2);
            DrawLayer(layer1, 1);
        }

        private ControlModel controlModel;

        private void MainWindow_Load(object sender, EventArgs e)
        {

        }

        private void MainWindow_Paint(object sender, PaintEventArgs e)
        {

        }
    }
}
