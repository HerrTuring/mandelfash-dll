using System;
using System.Collections.Generic;
using System.Drawing;

using Mandelfash;

namespace DLLTester
{
    public partial class Form : System.Windows.Forms.Form
    {
        public Form()
        {
            InitializeComponent();
        }

        private void execute_Click(object sender, EventArgs e)
        {
            // Base definitions.
            ColorCalculator calculator = new ColorCalculator();

            decimal x, y, z = 0;

            decimal xStart, xLong, xEnd, xStep, yStart, yLong, yEnd, yStep;

            // These two blocks of code define the base values for the x's and y's fors.
            xStart = -2;
            xLong = 2.5m;
            xEnd = xStart + xLong;
            xStep = xLong / 1023;

            yStart = 1.221896383186706m;
            yLong = (xLong * 1000) / 1023;
            yEnd = -yLong + yStart;
            yStep = (yLong / 1000) * (-1);

            // Set the color code of the background. From 0 to 44. Anything not in between will result in an exception.
            calculator.setBackgroundColorCode(0);

            // Set the point in which the background ends.
            calculator.setBackgroundColorMode(2);

            // Sets datetime for the starting time text field.
            startBox.Text = DateTime.Now.ToString();

            //These ifs check for configurations in the checkboxes and text fields.
            if (loopLimitBox.Text != "")
                calculator.setLoopLimit(Int32.Parse(loopLimitBox.Text));

            if (deactivateBlackBypass.Checked)
                calculator.setBlackBypass(false);

            if (deactivateMultithreading.Checked)
                calculator.setMultithreading(false);

            if (blackLoop.Checked)
                calculator.setBlackLoopStatus(true);

            if (invertRGB.Checked)
                calculator.setInvertedRGB(true);

            Bitmap image = new Bitmap(1000, 1023);
            int xCount = 0;

            for (x = xStart; x < xEnd; x += xStep)
            {
                List<List<int>> results = new List<List<int>>();
                for (y = yStart; y > yEnd; y += yStep)
                {
                    // Calculator starts here with x, y and z.
                    calculator.startCalculator(x.ToString(), y.ToString(), z.ToString());
                }

                // After all y possibilities are sent we use the function getResults below to feed the for that will render the image with the pixels defined.
                int yCount = 0;
                foreach(List<int> pixel in calculator.getResults())
                {
                    int alpha = 255;
                    if (pixel[0] == 255 && pixel[1] == 255 && pixel[2] == 255)
                        alpha = 0;

                    image.SetPixel(yCount, 1022 - xCount, Color.FromArgb(alpha, pixel[0], pixel[1], pixel[2]));

                    yCount++;
                }
                xCount++;

                // Sends buffered image to the form.
                mandelfashPicture.Image = image;

                // Sends the xCount and the current time so we know how much time it has passed and what line we are of the image.
                counterBox.Text = xCount.ToString();
                endBox.Text = DateTime.Now.ToString();
            }

            // If asked to benchmark the system will call the benchmarking method.
            if (benchmarking.Checked)
                calculator.saveBenchmark();
        }
    }
}
