using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Tarea4
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        static Arbol arbol = new Arbol();
        private void button1_Click(object sender, EventArgs e)
        {
            if((maskedTextBox1.Text != "")&&(maskedTextBox1.Text != " ")&&(maskedTextBox1.Text != ";"))
            {
                char dato = Convert.ToChar(maskedTextBox1.Text);
                arbol.InsertarNodoUser(dato);
                var fileName = Path.GetFullPath("Archivos/graphiz.txt");
                string dot = arbol.ToDotGraph();
                arbol.SaveToFile(fileName, dot);
                string path = Directory.GetCurrentDirectory();
                GenerateGraph(fileName, path);
                arbol.preorden = "";
                arbol.ImprimirPreOrden();
                arbol.postorden = "";
                arbol.ImprimirPostOrden();
                arbol.inorden = "";
                arbol.ImprimirInOrden();
                label5.Text = arbol.preorden;
                label6.Text = arbol.postorden;
                label7.Text = arbol.inorden;
                System.Diagnostics.Process.Start(Path.GetFullPath("Archivos/graphiz.jpg"));
            }
            
        }
        

        private static void GenerateGraph(string fileName, string path)
        {
            try
            {
                var command = string.Format("dot -Tjpg {0} -o {1}", Path.Combine(path, fileName), Path.Combine(path, fileName.Replace(".txt", ".jpg")));
                var procStartInfo = new System.Diagnostics.ProcessStartInfo("cmd", "/C " + command);
                var proc = new System.Diagnostics.Process();
                proc.StartInfo = procStartInfo;
                proc.Start();
                proc.WaitForExit();
            }
            catch (Exception x)
            { }
        }
    }
}
