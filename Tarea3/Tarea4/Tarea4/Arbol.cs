using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Tarea4
{
    class Arbol
    {
        public string preorden = "";
        public string postorden = "";
        public string inorden = "";
        public Nodo raiz = null;
        public Nodo siguient, anterior, recorrido, auxiliar;
        //Insertar datos en el arbol
        public void InsertarNodoUser(char Dato)
        {
            Nodo nuevo = new Nodo(Dato);
            nuevo.dato = Dato;
            if (raiz == null) { raiz = nuevo; }
            else if (DatoBuscado(Dato) != null) { MessageBox.Show("El dato ya existe en el arbol", "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Error); }
            else
            {
                anterior = null;
                recorrido = raiz;
                while (recorrido != null)
                {
                    anterior = recorrido;
                    if (Dato < recorrido.dato) { recorrido = recorrido.izquierda;}
                    else { recorrido = recorrido.derecha; }
                }
                if (Dato < anterior.dato)
                {
                    anterior.izquierda = nuevo;
                }
                else
                {
                    anterior.derecha = nuevo;
                }
            }
        }

        //Comprobar existencia de dato
        public Nodo DatoBuscado(char dato)
        {
            return Buscardato(dato, raiz);
        }
        public Nodo Buscardato(char Dato, Nodo recorrido)
        {
            while (recorrido.dato != Dato)
            {
                if (Dato < recorrido.dato)
                {
                    recorrido = recorrido.izquierda;
                }
                else
                {
                    recorrido = recorrido.derecha;
                }
                if (recorrido == null)
                {
                    return null;
                }
            }
            return recorrido;
        }

        //Crear Graphiz
        public string ToDotGraph()
        {
            StringBuilder b = new StringBuilder();
            b.Append("digraph G {" + Environment.NewLine);
            b.Append(ToDot(raiz));
            b.Append("}");
            return b.ToString();
        }
        public string ToDot(Nodo node)
        {
            StringBuilder b = new StringBuilder();
            if (node.izquierda != null)
            {
                b.AppendFormat("{0}->{1}{2}", node.dato.ToString(), node.izquierda.dato.ToString(), Environment.NewLine);
                b.Append(ToDot(node.izquierda));
            }

            if (node.derecha != null)
            {
                b.AppendFormat("{0}->{1}{2}", node.dato.ToString(), node.derecha.dato.ToString(), Environment.NewLine);
                b.Append(ToDot(node.derecha));
            }
            return b.ToString();
        }
        public void SaveToFile(string fileName, string dot)
        {
            TextWriter tw = new StreamWriter(fileName);
            tw.WriteLine(dot);
            tw.Close();

        }

        //Recorrido Preorden
        private void ImprimirPreOrden(Nodo nodo)
        {
            if (nodo != null)
            {
                preorden = preorden + " " + nodo.dato + ",";
                ImprimirPreOrden(nodo.izquierda);
                ImprimirPreOrden(nodo.derecha);
            }
        }
        public void ImprimirPreOrden()
        {
            ImprimirPreOrden(raiz);
        }

        //Recorrido Inorden
        private void ImprimirInOrden(Nodo nodo)
        {
            if (nodo != null)
            {
                ImprimirInOrden(nodo.izquierda);
                inorden = inorden + " " + nodo.dato + ",";
                ImprimirInOrden(nodo.derecha);
            }
        }
        public void ImprimirInOrden()
        {
            ImprimirInOrden(raiz);
        }

        //Recorrido Postorden
        private void ImprimirPostOrden(Nodo nodo)
        {
            if (nodo != null)
            {
                ImprimirPostOrden(nodo.izquierda);
                ImprimirPostOrden(nodo.derecha);
                postorden = postorden + " " + nodo.dato + ",";
            }
        }
        public void ImprimirPostOrden()
        {
            ImprimirPostOrden(raiz);
        }
    }
}
