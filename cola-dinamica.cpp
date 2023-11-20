#include <iostream>

template<class T>
class ColaEstatica;

template<class T>
class node {
private:
    T data;
    node<T>* sig;
public:
    node() :sig(nullptr) {};
    friend class ColaEstatica<T>;
};

class Constancia {
private:
    int materias;
    std::string nombre, carrera;
    float promedio;
public:
    Constancia() {
        materias = 0;
        nombre = " ";
        carrera = " ";
        promedio = 0;
    }
    Constancia(int mat, std::string nombre, std::string car, float prom) {
        materias = mat;
        nombre = nombre;
        carrera = car;
        promedio = prom;
    }

    friend bool operator == (Constancia& c1, Constancia& c2) {
        return (
            c1.nombre == c2.nombre &&
            c1.carrera == c2.carrera  &&
            c1.materias == c2.materias &&
            c1.promedio == c2.promedio
            );
    }

    friend bool operator != (Constancia& c1, Constancia& c2) {
        return !(c1 == c2);
    }

    friend Constancia operator + (Constancia& c1, Constancia& c2) {
        return Constancia(c1.materias + c2.materias, c1.nombre + c2.nombre,
            c1.carrera + c2.carrera, c1.promedio + c2.promedio);
    }

    friend bool operator > (Constancia& c1, Constancia& c2) {
        return c1.promedio > c2.promedio;
    }

    friend bool operator < (Constancia& c1, Constancia& c2) {
        return c1.promedio < c2.promedio;
    }

    friend std::istream& operator >> (std::istream& i, Constancia& e) {
        std::cout << "Total de materias aprovadas del alumno: ";
        i >> e.materias;

        std::cout << "Ingresa el nombre de alumno: ";
        std::cin.ignore();
        i >> e.nombre;

        std::cout << "Ingresa la carrera del alumno: ";
        std::cin.ignore();
        i >> e.carrera;

        std::cout << "Ingresa el promedio del alumno: ";
        i >> e.promedio;

        return i;
    }

    friend std::ostream& operator << (std::ostream& o, Constancia& e) {
        o << "Materias aprovadas: " << e.materias << std::endl;
        o << "Nombre: " << e.nombre << std::endl;
        o << "Carrera: " << e.carrera << std::endl;
        o << "Promedio: " << e.promedio << std::endl;

        return o;
    }
};

template<class T>
class ColaEstatica {
private:
    node<T>* lista;
    void insertar(node<T>* pos, T elem);
    bool eliminar(node<T>* pos);
public:
    ColaEstatica() :lista(nullptr) {};
    bool vacia()const;
    node<T>* ultimo()const;
    node<T>* primero()const;
    node<T>* anterior(node<T>* pos)const;
    void imprimir()const;
    void enqueue(Constancia& constancia);
    void dequeue();
};

template<class T>
void ColaEstatica<T>::imprimir()const {
    node<T>* aux = lista;
    while (aux != nullptr) {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << aux->data << std::endl;
        aux = aux->sig;
        std::cout << "----------------------------------------" << std::endl;
    }
}

template<class T>
bool ColaEstatica<T>::eliminar(node<T>* pos) {
    if (vacia() || pos == nullptr) {
        return false;
    }
    if (pos == lista) {
        lista = lista->sig;
    }
    else {
        anterior(pos)->sig = pos->sig;
    }
    delete pos;
    return true;
}

template<class T>
void ColaEstatica<T>::insertar(node<T>* pos, T elem) {
    node<T>* aux = new node<T>;
    aux->data = elem;

    if (pos == nullptr) {
        aux->sig = lista;
        lista = aux;
    }
    else {
        aux->sig = pos->sig;
        pos->sig = aux;
    }
}

template<class T>
node<T>* ColaEstatica<T>::anterior(node<T>* pos)const {
    if (vacia() || pos == nullptr) {
        return nullptr;
    }
    node<T>* aux = lista;
    while (aux != nullptr && aux->sig != pos) {
        aux = aux->sig;
    }
    return aux;
}

template<class T>
node<T>* ColaEstatica<T>::primero()const {
    if (vacia()) {
        return nullptr;
    }
    return lista;
}


template<class T>
node<T>* ColaEstatica<T>::ultimo()const {
    if (vacia()) {
        return nullptr;
    }
    node<T>* aux = lista;
    while (aux->sig != nullptr) {
        aux = aux->sig;
    }
    return aux;
}

template<class T>
bool ColaEstatica<T>::vacia()const {
    if (lista == nullptr)
        return true;
    return false;
}

template<class T>
void ColaEstatica<T>::enqueue(Constancia& constancia) {
    insertar(ultimo(), constancia);
}

template<class T>
void ColaEstatica<T>::dequeue() {
    std::cout << "-----------------------------     Reporte:    -----------------------------" << std::endl;
    std::cout << primero()->data;
    std::cout << "---------------------------------------------------------------------------" << std::endl;
    eliminar(primero());
}

int main()
{
    ColaEstatica<Constancia> micola;
    int opcion;
    Constancia constancia;

    do {
        std::cout << "---------------Menu---------------" << std::endl;
        std::cout << "1. Dar de alta solicitud de un alumno" << std::endl;
        std::cout << "2. Elaborar una constancia" << std::endl;
        std::cout << "3. Salir" << std::endl;
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
        case 1:
            std::cin >> constancia;
            micola.enqueue(constancia);
            break;
        case 2:
            if (micola.vacia()) {
                std::cout << "La cola esta vacia" << std::endl;
            }
            else {
                micola.dequeue();
            }
            break;
        case 3:
            std::cout << "Saliendo..." << std::endl;
            break;
        default:
            std::cout << "Opcion incorrecta :(" << std::endl;
            break;
        }
    } while (opcion != 3);

    return 0;
}
