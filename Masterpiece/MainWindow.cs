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

            Sensor sensor = new Sensor(SensorType.TEMPERATURE_SENSOR, 0, 50, 2);
            controlModel = new ControlModel(sensor, 5);

            Timer timer = new Timer();
            timer.Interval = 1000;
            timer.Tick += OnTimer;
            timer.Start();
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
        }

        private ControlModel controlModel;
    }
}
