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
          
            for (uint i = 0; i < 5; ++i)
            {
                sensorMemory.AddLayer();
            }
            graphic = this.CreateGraphics();

            for (int i = 0; i < 16; i++) granuleLabel[i] = new Label();
            Timer timer = new Timer();
            timer.Interval = 2000;
            timer.Tick += OnTimer;
            timer.Start();
            draw();
        }

        public Label[] granuleLabel = new Label[17];
     
        Graphics graphic;
        int inner = 10;
int outer = 40;
int levels = 5;
int width = 971;
int height = 500;
int count0 = (5 - 1) * 3;

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


          
        /*    foreach (Granule granule in layer)
            {
  graphic.DrawEllipse(Pens.Black, startX, startY, 50, 50);
  startX = startX + 75;
               
            }*/
        }

            void draw() {
  //background(255, 255, 255);
 // strokeWeight(2);
               
  int i, j;
  for(i = 0; i < levels - 1; ++i) {
    for(j = 0; j < i; ++j) {
      graphic.DrawLine(Pens.Black,levelXBig(j, i), levelY(levels + 1 - i), levelXBig(j, i + 1), levelY(levels - i));
      graphic.DrawEllipse(Pens.Blue, levelXBig(j, i)-20, levelY(levels + 1 - i)-20, outer, outer);
      graphic.DrawLine(Pens.Black, levelXBig(j, i), levelY(levels + 1 - i), levelXBig(j + 1, i + 1), levelY(levels - i));
   //   graphic.DrawEllipse(Pens.Blue, levelXBig(j + 1, i + 1) - 20, levelY(levels - i) - 20, outer, outer);
   
    }
  }
  for(j = 0; j < i; ++j) {
      graphic.DrawLine(Pens.Black, levelXBig(j, i), levelY(levels + 1 - i), levelXSmall(2 * j, count0 / 3 * 2), levelY(levels - i));
      graphic.DrawEllipse(Pens.Blue, levelXBig(j, i)-20, levelY(levels + 1 - i)-20, outer, outer);
      graphic.DrawLine(Pens.Black, levelXBig(j, i), levelY(levels + 1 - i), levelXSmall(2 * j + 1, count0 / 3 * 2), levelY(levels - i));
     // graphic.DrawEllipse(Pens.Blue, levelXSmall(2 * j + 1, count0 / 3 * 2) - 20, levelY(levels - i) - 20, outer, outer);
  }
  ++i;
  for(j = 0; j < count0 / 3 * 2; ++j) {
      graphic.DrawLine(Pens.Black, levelXSmall(j, count0 / 3 * 2), levelY(levels + 1 - i), levelXSmall(j / 2 * 3 + j % 2, count0), levelY(levels - i));
      graphic.DrawEllipse(Pens.Blue, levelXSmall(j, count0 / 3 * 2)-20, levelY(levels + 1 - i)-20, outer, outer);
      graphic.DrawEllipse(Pens.Blue, levelXSmall(j / 2 * 3 + j % 2, count0) - 20, levelY(levels - i) - 20, outer, outer);
    graphic.DrawLine(Pens.Black,(levelXSmall(j, count0 / 3 * 2)), levelY(levels + 1 - i), levelXSmall(j / 2 * 3 + j % 2 + 1, count0), levelY(levels - i));
    graphic.DrawEllipse(Pens.Blue, levelXSmall(j / 2 * 3 + j % 2 + 1, count0) - 20, levelY(levels - i) - 20, outer, outer);
  }



  for (uint ii = 0; ii < sensorMemory.LayerCount; ++ii)
  {
    //     float g = gamma(alpha[time][i][j], betta[time][i][j]);
  //  fill(255 * (1 - g), 255 * (1 - g), 255); 
      List<Granule> layer = sensorMemory.GetGranules(ii);
      //j = layer.Count;
      int y = layer.Count;
    //  graphic.DrawEllipse(Pens.Blue,levelX(i, j,y), levelY(i), outer, outer);
    //float a = (alpha[time][i][j] + 1) / 2;
    //fill(255 * a, 255 * (1 - a), 0);
    //ellipse(levelX(i, j), levelY(i), inner, inner);
    //fill(255, 255, 255); 
  }


  
 // fill(0, 0, 0);
 // textSize(64);
  //text(data[time], 50, height / 3 * 2);
  //text(betta[time][0][0], 50, height / 3. * 2.);
  //text(gamma(alpha[time][0][0], betta[time][0][0]), 50, height / 3. * 2. + 50);
  //text(gamma(0, betta[time][0][0]), 50, height / 3. * 2. + 50);
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
           
        

        void OnTimer(Object sender, EventArgs e)
        {
            valueBox.Clear();
            sensor.Update();
            sensorMemory.Update(sensor.Value);

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
            draw();
            //DrawLayer(layer2, 2);
            //DrawLayer(layer1, 1);
        }

        private Sensor sensor = new Sensor(SensorType.TEMPERATURE_SENSOR, 0, 24, 2);
        private SensorMemory sensorMemory = new SensorMemory(0, 24, 2, 3);
    }
}
