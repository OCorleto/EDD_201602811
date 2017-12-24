using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tarea4
{
    class Nodo
    {
        
        public Nodo izquierda { get; set; }
        public Nodo derecha { get; set; }
        public char dato { get; set; }
        public Nodo(char Dato)
        {
            this.dato = Dato;
            this.izquierda = this.derecha = null;
        }

    }
}
