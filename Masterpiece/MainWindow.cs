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

            // add 5 layers
            for (uint i = 0; i < 5; ++i)
            {
                sensorMemory.AddLayer();
            }
            graphic = this.CreateGraphics();
<<<<<<< HEAD

=======
            Sensor sensor = new Sensor(SensorType.TEMPERATURE_SENSOR, 0, 50, 2);
//            controlModel = new ControlModel(sensor, 5);
>>>>>>> Remove ControlModel class
            for (int i = 0; i < 16; i++) granuleLabel[i] = new Label();
            Timer timer = new Timer();
            timer.Interval = 2000;
            timer.Tick += OnTimer;
            timer.Start();
        }

        public Label[] granuleLabel = new Label[17];

        Graphics graphic;
        void DrawLayer(List<Granule> layer, int number)
        {

            int heightWindow = this.Height;
            int widghtWindow = this.Width;
            int startX = 50;
            graphic.DrawRectangle(Pens.Black, 50, 100, widghtWindow - 100, heightWindow - 150);
            graphic.DrawLine(Pens.Black, startX + 50, ((heightWindow) / 2), widghtWindow - 150, ((heightWindow) / 2));
            int lineWidght = widghtWindow - 150 - startX - 50;
            int sizeX = 0;
            if (lineWidght % layer.Count > 5)
                sizeX = lineWidght / layer.Count + 1;
            else
                sizeX = lineWidght / layer.Count;
            int sizeY = 30 * number;
            startX = startX + 50;
            Random random = new Random();
            Brush brush;
            brush = new SolidBrush(Color.FromArgb(random.Next(255), random.Next(255), random.Next(255), random.Next(255)));
            for (int i = 1; i < layer.Count + 1; i++)
            {
                brush = new SolidBrush(Color.FromArgb(random.Next(255), random.Next(255), random.Next(255), random.Next(255)));
                graphic.FillRectangle(brush, startX, ((heightWindow) / 2), sizeX, sizeY + 20);
                startX = startX + sizeX;

            }
            startX = lineWidght / layer.Count + 1;
            int start_lab = (heightWindow) / 2 + 5;
            int index = 0;
            if (number > 1)
            {
                start_lab = (heightWindow) / 2 + 50;
                index = 11;
            }


            foreach (Granule granule in layer)
            {

                granuleLabel[index].Text = "";
                granuleLabel[index].Location = new System.Drawing.Point(startX + 50, start_lab);
                granuleLabel[index].Text = granule.Alpha.ToString();
                granuleLabel[index].BackColor = System.Drawing.Color.Transparent;
                if (granuleLabel[index].Text.Length > 3)
                    granuleLabel[index].Text.Substring(0, 3);
                granuleLabel[index].Width = 40;
                startX = startX + sizeX;
                this.Controls.AddRange(new Control[] { granuleLabel[index] });
                index++;
            }

        }

        void OnTimer(Object sender, EventArgs e)
        {
            valueBox.Clear();
<<<<<<< HEAD
            sensor.Update();
            sensorMemory.Update(sensor.Value);
=======
//            controlModel.Update();
            valueBox.Text += "Layer 1: ";
            List<Granule> layer1 = new List<Granule>();// = controlModel.SensorMemory.GetGranules(0);

>>>>>>> Remove ControlModel class

            for (uint i = 0; i < sensorMemory.LayerCount; ++i)
            {
                List<Granule> layer = sensorMemory.GetGranules(i);
                valueBox.Text += String.Format("Layer {0}:\r\nAlpha: ", i);
                foreach (Granule granule in layer)
                {
                    valueBox.Text += granule.Alpha + " ";
                }
                valueBox.Text += "\r\nBeta: ";
                foreach (Granule granule in layer)
                {
                    valueBox.Text += granule.Beta + " ";
                }
                valueBox.Text += "\r\n\r\n";
                DrawLayer(layer, (int)i);
            }

<<<<<<< HEAD
            //DrawLayer(layer2, 2);
            //DrawLayer(layer1, 1);
        }

        private Sensor sensor = new Sensor(SensorType.TEMPERATURE_SENSOR, 0, 24, 2);
        private SensorMemory sensorMemory = new SensorMemory(0, 24, 2, 3);
=======
            valueBox.Text += "\r\n\r\nLayer 2: ";
            //if (controlModel.SensorMemory.LayerCount >= 2)
            //{
            //    controlModel.SensorMemory.RemoveTopLayer();
            //}
            //controlModel.SensorMemory.AddLayer(2);
            List<Granule> layer2 = new List<Granule>();// = controlModel.SensorMemory.GetGranules(1);
            foreach (Granule granule in layer2)
            {
                valueBox.Text += granule.Alpha + " ";
            }
            DrawLayer(layer2, 2);
            DrawLayer(layer1, 1);
        }

//        private ControlModel controlModel;
>>>>>>> Remove ControlModel class
    }
}
