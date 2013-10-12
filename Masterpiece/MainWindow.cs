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
            CoreWrapper.SensorMemoryWrapper sensorMemory = new CoreWrapper.SensorMemoryWrapper();
            valueBox.Text += sensorMemory.getSomeValue();
        }
    }
}
