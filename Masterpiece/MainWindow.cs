using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Mastepiece
{
    public partial class MainWindow : Form
    {
        public MainWindow()
        {
            InitializeComponent();
            CoreWrapper.SensorMemory sensorMemory = new CoreWrapper.SensorMemory(0, 30, 10);
            sensorMemory.Update(12.5);
            valueBox.Text += sensorMemory.GetGranules(0)[1].FuzzyFactor;
        }
    }
}
