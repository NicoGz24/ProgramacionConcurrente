En un examen final hay N alumnos y P profesores. Cada alumno resuelve su examen, lo
entrega y espera a que alguno de los profesores lo corrija y le indique la nota. Los
profesores corrigen los exámenes respectando el orden en que los alumnos van entregando.
a) Considerando que P=1.
b) Considerando que P>1.
c) Ídem b) pero considerando que los alumnos no comienzan a realizar su examen hasta
que todos hayan llegado al aula.
Nota: maximizar la concurrencia y no generar demora innecesaria

a)Considerando que P=1.

Process Alumno[id:0..N-1]
{
    text examen
    int nota
    examen = RealizarExamen()
    Coordinador!corregir(id,examen)
    Profesor?resultado(nota)
}

Process Coordinador::
{
    text examen
    cola buffer
    int idA
    do Alumno[*]?corregir(idA,examen) -> push(buffer,idA,examen)
    □ (not empty(buffer)), Profesor?pedido() -> Profesor!corregir(pop(buffer))
    od
}

Process Profesor::
{
    text examen
    int nota, idA
    for i=0 to N-1
    {
        Coordinador!pedido()
        Coordinador?corregir(idA, examen)
        nota = CorregirExamen(examen)
        Alumno[idA]!resultado(nota)
    }
}
//--------------------------------------------------------------------------------
b) Considerando que P>1.

Process Alumno[id:0..N-1]
{
    text examen
    int nota
    examen = RealizarExamen()
    Coordinador!corregir(id,examen)
    Profesor[*]?resultado(nota)
}

Process Coordinador::
{
    text examen
    cola buffer
    int idA, idP
    do Alumno[*]?corregir(idA,examen) -> push(buffer,idA,examen)
    □ (not empty(buffer)), Profesor[*]?pedido(idP) -> Profesor[idP]!corregir(pop(buffer))
    od
}

Process Profesor[id:0..P-1]
{
    text examen
    int nota, idA
    while(true)
    {
        Coordinador!pedido(id)
        Coordinador?corregir(idA, examen)
        nota = CorregirExamen(examen)
        Alumno[idA]!resultado(nota)
    }
}

//--------------------------------------------------------------------------------

c) Ídem b) pero considerando que los alumnos no comienzan a realizar su examen hasta
que todos hayan llegado al aula.

Process Alumno[id:0..N-1]
{
    text examen
    int nota
    Barrera!llegue()
    Barrera?comenzar()
    examen = RealizarExamen()
    Coordinador!corregir(id,examen)
    Profesor[*]?resultado(nota)
}

Process Barrera::
{
    int cant = 0
    do 
        Alumno[*]?llegue() -> cant++ 
    od
    for i = 0 to N-1 {Alumno[i]!comenzar()}
}

Process Coordinador::
{
    text examen
    cola buffer
    int idA, idP
    do Alumno[*]?corregir(idA,examen) -> push(buffer,idA,examen)
    □ (not empty(buffer)), Profesor[*]?pedido(idP) -> Profesor[idP]!corregir(pop(buffer))
    od
}

Process Profesor[id:0..P-1]
{
    text examen
    int nota, idA
    while(true)
    {
        Coordinador!pedido(id)
        Coordinador?corregir(idA, examen)
        nota = CorregirExamen(examen)
        Alumno[idA]!resultado(nota)
    }
}
