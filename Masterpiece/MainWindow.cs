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
using VisualGraphModel.Abstract;
using VisualGraphModel.Concrete;
using VisualGraphModel.Coordinates;
using GraphModel.Concrete;


namespace Mastepiece
{
    public partial class MainWindow : Form
    {
        public MainWindow()
        {
            InitializeComponent();
           // vg = this.editGraph1.vg;
          //  mediator = this.editGraph1.mediator;
            spaceY = (height - levels * 2 * outer) / 2 / levels;
 spaceXBig = (width - levels * 2 * outer) / 2 / levels;
 spaceXSmall = (width - (count0 + 1) * 2 * outer) / 2 / (count0 + 1);
            // add 5 layers
          
            for (uint i = 0; i < 43; ++i)
            {
                sensorMemory.AddLayer();
            }
            graphic = this.CreateGraphics();

            for (int i = 0; i < 16; i++) granuleLabel[i] = new Label();
            Timer timer = new Timer();
            timer.Interval = 2000;
            timer.Tick += OnTimer;
            timer.Start();
            //draw();
        }

        public Label[] granuleLabel = new Label[17];
     
        Graphics graphic;
     
int outer = 10;
int levels = 44;
int width =1600;
int height = 1000;
int count0 = (44 - 1) * 3;

        float spaceY ;
float spaceXBig;
float spaceXSmall ;

float levelY(int l) {
  return spaceY + outer + l * 2 * (outer + spaceY);
}

float levelXBig(int l, int count) {
  float shift = width / 2 - count * outer - count * spaceXBig; 
  return (shift + spaceXBig + l * 2 * (outer  + spaceXBig))/2;
}

float levelXSmall(int l, int count) {
  //float shift = width / 2. - count * outer - count * spaceXSmall; 
  //return shift + spaceXSmall + l * 2 * (outer  + spaceXSmall);
  return width / (count + 1) * (l + 1);
}

float levelX(int i, int j,int y) {
  return i < 2 ? levelXSmall(j, y/*alpha[0][i].length*/) : levelXBig(j, /*alpha[0][i].length*/y);
}


        void DrawLayer(List<Granule> layer, int number)
        {
            Random random = new Random();
            Brush brush;

            int heightWindow = this.Height;
            int widghtWindow = this.Width;
            int startX = 50;
            int startY = (heightWindow) / 2 - 100;
          //  graphic.DrawRectangle(Pens.Black, 50, 100, widghtWindow - 100, heightWindow - 150);


 
        }

        double [][] alpha = new double[44][];
    
            void draw() {
  //background(255, 255, 255);
 // strokeWeight(2); 
                int radius = 5;
                double a = 0 ;
                SolidBrush mySolidBrush = new SolidBrush(Color.FromArgb(255, (int)(255 * 1), (int)(255 * (1 - 1)), 0));     
  int i, j;
  for(i = 0; i < levels - 1; ++i) {
    for(j = 0; j < i; ++j) {
      graphic.DrawLine(Pens.Black,levelXBig(j, i), levelY(levels + 1 - i), levelXBig(j, i + 1), levelY(levels - i));

      graphic.DrawLine(Pens.Black, levelXBig(j, i), levelY(levels + 1 - i), levelXBig(j + 1, i + 1), levelY(levels - i));

      if (alpha[levels - i].Length > j) { a = (alpha[levels - i][j] + 1) / 2; }
      mySolidBrush = new SolidBrush(Color.FromArgb(255, (int)(255 * a), (int)(255 * (1 - a)), 0));
     graphic.FillEllipse(mySolidBrush, levelXBig(j, i) - radius, levelY(levels + 1 - i) - radius, outer, outer);
    }
  }

  for (j = 0; j < alpha[2].Length; ++j)
  {
      
      graphic.DrawLine(Pens.Black, levelXBig(j, i), levelY(levels + 1 - i), levelXSmall(2 * j, count0 / 3 * 2), levelY(levels - i));
    
      graphic.DrawLine(Pens.Black, levelXBig(j, i), levelY(levels + 1 - i), levelXSmall(2 * j + 1, count0 / 3 * 2), levelY(levels - i));
  
          a = (alpha[2][j] + 1) / 2;
          mySolidBrush = new SolidBrush(Color.FromArgb(255, (int)(255 * a), (int)(255 * (1 - a)), 0));
          graphic.FillEllipse(mySolidBrush, levelXBig(j, i) - radius, levelY(levels + 1 - i) - radius, outer, outer);
      
   
  }
  graphic.FillEllipse(mySolidBrush, levelXBig(j, i) - radius, levelY(levels + 1 - i) - radius, outer, outer);
  ++i;
  for(j = 0; j < count0 / 3 * 2; ++j) {
      graphic.DrawLine(Pens.Black, levelXSmall(j, count0 / 3 * 2), levelY(levels + 1 - i), levelXSmall(j / 2 * 3 + j % 2, count0), levelY(levels - i));

    graphic.DrawLine(Pens.Black,(levelXSmall(j, count0 / 3 * 2)), levelY(levels + 1 - i), levelXSmall(j / 2 * 3 + j % 2 + 1, count0), levelY(levels - i));
    if (alpha[1].Length > j)
    {
        a = (alpha[1][j] + 1) / 2;
        mySolidBrush = new SolidBrush(Color.FromArgb(255, (int)(255 * a), (int)(255 * (1 - a)), 0));
        graphic.FillEllipse(mySolidBrush, levelXSmall(j, count0 / 3 * 2) - radius, levelY(levels + 1 - i) - radius, outer, outer);
    }
    else
    {
        graphic.FillEllipse(mySolidBrush, levelXSmall(j, count0 / 3 * 2) - radius, levelY(levels + 1 - i) - radius, outer, outer);
    }

    if (alpha[0].Length > j)
    {
        a = (alpha[0][j / 2 * 3 + j % 2] + 1) / 2;
        mySolidBrush = new SolidBrush(Color.FromArgb(255, (int)(255 * a), (int)(255 * (1 - a)), 0));
        graphic.FillEllipse(mySolidBrush, levelXSmall(j / 2 * 3 + j % 2, count0) - radius, levelY(levels - i) - radius, outer, outer);
           
       a = (alpha[0][j / 2 * 3 + j % 2 ] + 1) / 2; 
mySolidBrush = new SolidBrush(Color.FromArgb(255,(int)(255 * a),(int) (255 * (1 - a)), 0));
       graphic.FillEllipse(mySolidBrush, levelXSmall(j / 2 * 3 + j % 2 + 1, count0) - radius, levelY(levels - i) - radius, outer, outer);
      
    }

  }


}
        




           /* graphic.DrawLine(Pens.Black, startX + 50, ((heightWindow) / 2), widghtWindow - 150, ((heightWindow) / 2));
            int lineWidght = widghtWindow - 150 - startX - 50;
            int sizeX = 0;
            if (lineWidght % layer.Count > 5)
                sizeX = lineWidght / layer.Count + 1;
            else
                sizeX = lineWidght / layer.Count;
            int sizeY = 30 * number;
            startX = startX + 50;
         
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
            }*/
           
        
        int [] value={100,92,88,79,70,68,60,51,42,36,25,16,8,2};
        int k = 0; 
        void OnTimer(Object sender, EventArgs e)
        {
            valueBox.Clear();
            sensor.Update();
         //k  = 0;
            sensorMemory.Update(value[k]);
            valueBox.Text += value[k];
            k++;
            if (k == 14) k = 0;
            

            for (uint i = 0; i < sensorMemory.LayerCount; ++i)
            {
                List<Granule> layer = sensorMemory.GetGranules(i);
                valueBox.Text += String.Format("Layer {0}:\r\nAlpha: ", i);
                int j=0;
                foreach (Granule granule in layer)
                {
                    valueBox.Text += granule.Alpha + " ";
                if (j==0)    alpha[i] = new double[layer.Count];
                    alpha[i][j] = granule.Alpha;
                    j++;
                }
                valueBox.Text += "\r\nBeta: ";
                foreach (Granule granule in layer)
                {
                    valueBox.Text += granule.Beta + " ";
                }
                valueBox.Text += "\r\n\r\n";
                DrawLayer(layer, (int)i);
            }
            draw();
            //DrawLayer(layer2, 2);
            //DrawLayer(layer1, 1);
        }

        private Sensor sensor = new Sensor(SensorType.TEMPERATURE_SENSOR, 0, 255, 2);
        private SensorMemory sensorMemory = new SensorMemory(0,255, 2, 3);
    }
}
