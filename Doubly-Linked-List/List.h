#ifndef _LIST_H
#define _LIST_H

#include "Node.h"
#include <iostream>
#include <string>

/*
   Die Klasse List dient zur Verwaltung von Knoten (Node). Mit Hilfe der Klasse
   List kann ein Stapel oder Warteschlange realisiert werden.
*/
template <typename T>
class List
{
private:
    struct form
    {
        std::string start = "<< ";
        std::string zwischen = ", ";
        std::string ende = " >>\n";
    } list_form;

    Node<T>* m_head_tail; // Zeiger auf Kopf- und End-Element -> next der 1. Knoten;
    // -> prev der letzte Knoten
    int  m_list_size;  // Länge der Kette
    bool m_temp; // normalerweise false; ist true, wenn es sich um eine temporaere
    // Liste handelt die innerhalb der überladenen Operatoren angelegt wird
public:
    List();
    List(const List<T>& _List); // Kopie Konstruktor
    ~List();
    void insertFront(T value);     // Einfügen eines Knotens am Anfang
    void insertFront(List<T>& _List); // Einfügen einer vorhandenen Liste am Anfang
    void insertBack(T value);      // Einfügen eines Knotesn am Ende
    void insertBack(List<T>& _List);  // Einfügen einer vorhandenen Liste am Ende
    bool getFront(T& value);       // Entnehmen eines Knoten am Anfang
    bool getBack(T& value);        // Entnehmen eines Knoten am Ende
    bool del(T value);             // löschen eines Knotens [key]
    bool search(T value);          // Suchen eines Knoten
    bool swap(T value1, T value2); // Knoten in der Liste vertauschen
    int  size(void);               // Größe der Lise (Anzahl der Knoten)

    /* Mit der format - Methode kann die Ausgabe gesteuert werden : operator <<
    * start: string vor der Ausgabe der Liste
    * zwischen: string zwischen Listenknoten
    * ende: string am Ende der Liste 
    */
    void format(const std::string& start, const std::string& zwischen, const std::string& ende);
    

    List<T>& operator=(const List<T>& _List); // Zuweisungsoperator definieren
    List<T>& operator+(const List<T>& List_Append); // Listen zusammenführen zu einer Liste
    template<typename T>
    friend std::ostream& operator<<(std::ostream& stream, List<T>& Liste); // Ausgabeoperator überladen
};

/*
    Konstruktor für eine leere Liste
*/
template <typename T>
List<T>::List()
{
    m_head_tail = new Node<T>;
    m_list_size = 0;
    m_temp = false;
    m_head_tail->next = m_head_tail;
    m_head_tail->prev = m_head_tail;
}

/*
    Konstruktor mit Übergabe einer Liste, die dann kopiert wird.
    in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden
    sollen.
*/
template <typename T>
List<T>::List(const List<T>& _List)
{
    list_form = _List.list_form;

    m_head_tail = new Node<T>;

    m_list_size = 0;

    m_temp = _List.m_temp;

    m_head_tail->next = m_head_tail;
    m_head_tail->prev = m_head_tail;

    Node<T>* tmp_node = _List.m_head_tail->next;
    while (tmp_node != _List.m_head_tail)
    {
        m_head_tail->prev = new Node<T>(tmp_node->value, m_head_tail->prev->next, m_head_tail->prev);
        m_head_tail->prev->prev->next = m_head_tail->prev;
        m_list_size++;
        tmp_node = tmp_node->next;
    }
    /*
        Ist die übergebene Liste eine m_temporaere Liste? -> aus Operator +
    */
    if (_List.m_temp)
        delete& _List;
}

/*
    Dekonstruktor
    Alle Knoten der Liste müssen gelöscht werden, wenn die Liste gelöscht wird.
*/
template <typename T>
List<T>::~List()
{
    Node<T>* tmp_node = m_head_tail->next->next;

    while (tmp_node != m_head_tail)
    {
        delete tmp_node->prev;
        tmp_node = tmp_node->next;
    }
    delete tmp_node;
}

/*
    Einfuegen eines neuen Knotens am Anfang der Liste
    Einen neuen Knoten mit dem Wert value wird am Anfang der Liste einfügen
*/
template <typename T>
void List<T>::insertFront(T value)
{
    Node<T>* new_node = new Node<T>(value);

    if (this->m_list_size == 0) // leer
    {
        new_node->prev = m_head_tail;
        new_node->next = m_head_tail;
        m_head_tail->prev = new_node;
        m_head_tail->next = new_node;
    }
    else // nicht leer
    {
        new_node->next = m_head_tail->next;
        new_node->prev = m_head_tail;
        m_head_tail->next->prev = new_node;
        m_head_tail->next = new_node;
    }
    ++m_list_size;
}

/*
    Einfuegen der Liste _List am Anfang an einer vorhandenen Liste
    Die einzufuegenden Knoten werden uebernommen (nicht kopiert)
    Die einzufuegende Liste _List ist anschließend leer.
    Es darf keine Schleife und kein new benutzt werden.
*/
template <typename T>
void List<T>::insertFront(List<T>& _List)
{
    if (m_head_tail == _List.m_head_tail || _List.m_list_size == 0) // gleiches Objekt -> keine Aktion 
        return;

    _List.m_head_tail->prev->next = this->m_head_tail->next;
    _List.m_head_tail->next->prev = this->m_head_tail;
    this->m_head_tail->next->prev = _List.m_head_tail->prev;
    this->m_head_tail->next = _List.m_head_tail->next;

    _List.m_head_tail->prev = _List.m_head_tail->next = _List.m_head_tail;

    this->m_list_size += _List.m_list_size;
    _List.m_list_size = 0;
}

/*
    Einfuegen eines neuen Knotens am Ende der Liste
    Einen neuen Knoten mit dem Wert value wird am Ende der Liste einfügen
*/
template <typename T>
void List<T>::insertBack(T value)
{
    Node<T>* new_node = new Node<T>(value);

    if (this->m_list_size == 0) // leer
    {
        new_node->prev = m_head_tail;
        new_node->next = m_head_tail;
        m_head_tail->prev = new_node;
        m_head_tail->next = new_node;
    }
    else
    {
        m_head_tail->prev->next = new_node;
        new_node->prev = m_head_tail->prev;
        new_node->next = m_head_tail;
        m_head_tail->prev = new_node;
    }

    ++m_list_size;
}

/*
    Einfuegen der Liste _List am Ende einer vorhandenen Liste
    Die einzufuegenden Knoten werden uebernommen (nicht kopiert)
    Die einzufuegende Liste _List ist anschließend leer.
    Es darf keine Schleife und kein new benutzt werden.
*/
template <typename T>
void List<T>::insertBack(List<T>& _List)
{
    if (m_head_tail == _List.m_head_tail || _List.m_list_size == 0) // gleiches Objekt -> keine Aktion
        return;

    _List.m_head_tail->next->prev = this->m_head_tail->prev;
    _List.m_head_tail->prev->next = this->m_head_tail;
    this->m_head_tail->prev->next = _List.m_head_tail->next;
    this->m_head_tail->prev = _List.m_head_tail->prev;

    _List.m_head_tail->prev = _List.m_head_tail->next = _List.m_head_tail;

    this->m_list_size += _List.m_list_size;
    _List.m_list_size = 0;
}

/*
    entnehmen des Knotens am Anfang der Liste
    der Wert wird als Parameter zurueckgegeben
    der Knoten wird entnommen
    im Fehlerfall wird false zurückgegeben
*/
template <typename T>
bool List<T>::getFront(T& value)
{
    if (m_list_size == 0)
        return false;

    Node* temp = m_head_tail->next;
    value = temp->value;

    temp->next->prev = m_head_tail;
    m_head_tail->next = temp->next;

    delete temp;
    --m_list_size;

    return true;
}

/*
    entnehmen des Knotens am Ende der Liste
    der Wert wird als Parameter zurueckgegeben
    der Knoten wird entnommen
    im Fehlerfall wird false zurückgegeben
*/
template <typename T>
bool List<T>::getBack(T& value)
{
    if (m_list_size == 0)
        return false;

    Node<T>* temp = m_head_tail->prev;
    value = temp->value;

    m_head_tail->prev = temp->prev;
    m_head_tail->prev->next = m_head_tail;

    delete temp;
    --m_list_size;

    return true;
}

/*
    Loeschen eines gegebenen Knotens
    im Fehlerfall wird false zurückgegeben
*/
template <typename T>
bool List<T>::del(T value)
{
    if (m_list_size == 0)
        return false;

    Node* temp = m_head_tail->next;

    while (temp->value != value)
    {
        if (temp->next == m_head_tail)
            return false;
        temp = temp->next;
    }

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;

    delete temp;
    --m_list_size;

    return true;
}

/*
    suchen eines Knotens
    nicht gefunden -> Rueckgabe: false
*/
template <typename T>
bool List<T>::search(T value)
{
    if (m_list_size == 0)
        return false;

    Node<T>* temp = m_head_tail->next;

    while (temp->value != value)
    {
        if (temp->next == m_head_tail)
            return false;
        temp = temp->next;
    }
    return true;
}

/*
    Vertauschen von zwei Knoten
    Dabei werden die Zeiger der Knoten und deren Nachbarn veraendert.
    im Fehlerfall wird false zurueckgegeben
*/
template <typename T>
bool List<T>::swap(T value1, T value2)
{
    if (m_list_size < 2) // Wenn Liste Leer oder weniger als 2 Knoten besitzt -> Keine Aktion
        return false;

    Node<T>* temp1 = m_head_tail->next;
    while (temp1->value != value1)
    {
        if (temp1->next == m_head_tail)
            return false;
        temp1 = temp1->next;
    }

    Node<T>* temp2 = m_head_tail->next;
    while (temp2->value != value2)
    {
        if (temp2->next == m_head_tail)
            return false;
        temp2 = temp2->next;
    }

    if (temp1->next == temp2 || temp1->prev == temp2) // nachbar
    {
        if (temp1->next != temp2) // value2 vor value1 -> tauschen
        {
            Node<T>* ptr = temp2;
            temp2 = temp1;
            temp1 = ptr;
        }
        temp1->next = temp2->next;
        temp2->prev = temp1->prev;

        temp2->next->prev = temp1;
        temp1->prev->next = temp2;

        temp1->prev = temp2;
        temp2->next = temp1;
    }
    else // nicht nachbar
    {
        temp1->next->prev = temp2;
        temp2->next->prev = temp1;

        Node<T>* ptr = temp2->next;
        temp2->next = temp1->next;
        temp1->next = ptr;

        ptr = temp1->prev;
        temp1->prev = temp2->prev;
        temp2->prev = ptr;

        ptr->next = temp2;
        temp1->prev->next = temp1;

    }
    return true;
}

template <typename T>
int List<T>::size(void)
{
    return m_list_size;
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& _List)
{
    // in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden
    // sollen. Kopiert wird in das Objekt "this"
    if (this == &_List)
        return *this; //  !! keine Aktion notwendig
    list_form = _List.list_form;
    Node<T>* tmp_node;
    if (m_list_size)
    {
        Node<T>* tmp_del;
        tmp_node = m_head_tail->next;
        while (tmp_node !=
            m_head_tail) // Alle eventuell vorhandenen Knoten in this löschen
        {
            tmp_del = tmp_node;
            tmp_node = tmp_node->next;
            delete tmp_del;
        }
        m_list_size = 0;
        m_head_tail->next = m_head_tail;
        m_head_tail->prev = m_head_tail;
    }
    tmp_node = _List.m_head_tail->next; // Die Listen-Knotenwerte werden kopiert
    while (tmp_node != _List.m_head_tail)
    {
        insertBack(tmp_node->value);
        tmp_node = tmp_node->next;
    }
    if (_List.m_temp)
        delete& _List; // ist die übergebene Liste eine m_temporäre Liste? -> aus
    // Operator +
    return *this;
}

template <typename T>
List<T>& List<T>::operator+(const List<T>& List_Append)
{
    // Die Methode +
    // Es werden zwei Listen aneinander gehangen.
    // Dabei werden beide Ursprungslisten nicht verändert. Es entsteht eine neue
    // Ergebnisliste.
    Node<T>* tmp_node;
    List<T>* tmp;
    if (m_temp)
    { // this ist eine m_temporäre Liste und kann verändert werden
        tmp = this;
    }
    else
    {
        tmp =
            new List(*this); // this ist keine m_temporäre Liste -> Kopie erzeugen
        tmp->m_temp = true;    // Merker setzten, dass es sich um eine m_temporäre
        // Liste handelt
    }
    if (List_Append.m_list_size)
    { // anhängen der übergebenen Liste an tmp
        tmp_node = List_Append.m_head_tail->next;
        while (tmp_node != List_Append.m_head_tail)
        {
            tmp->insertBack(tmp_node->value);
            tmp_node = tmp_node->next;
        }
    }
    if (List_Append.m_temp)
        delete& List_Append; // wurde eine m_temporäre Liste übergeben, dann wird
    // diese gelöscht
    return *tmp;
}

template <typename T>
void List<T>::format(const std::string& start, const std::string& zwischen, const std::string& ende)
{
    // Setzen des Formates für die Ausgabesteuerung der Liste bei cout
    // das Format wird für den überladenen Operator << verwendet
    list_form.start = start;
    list_form.zwischen = zwischen;
    list_form.ende = ende;
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, List<T>& Liste)
{
    // Ausgabe der Liste mit cout
    stream << Liste.list_form.start;
    for (Node<T>* tmp = Liste.m_head_tail->next; tmp != Liste.m_head_tail;
        tmp = tmp->next)
        stream << tmp->value
        << (tmp->next == Liste.m_head_tail ? Liste.list_form.ende :
            Liste.list_form.zwischen);
    if (Liste.m_temp)
        delete& Liste; // wurde eine m_temporäre Liste übergeben, dann wird diese
    // gelöscht
    return stream;
}

#endif
