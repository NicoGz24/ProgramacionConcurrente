En una exposición aeronáutica hay un simulador de vuelo (que debe ser usado con
exclusión mutua) y un empleado encargado de administrar el uso del mismo. Hay P
personas que esperan a que el empleado lo deje acceder al simulador, lo usa por un rato y se
retira. El empleado deja usar el simulador a las personas respetando el orden de llegada.
Nota: cada persona usa sólo una vez el simulador.



Process Persona[id:0 to P-1]
{
    Administrador!llegue(id)
    Empleado?usarSimulador()
    UsarSimilador()
    Empleado!liberarSimulador()
}


Process Administrador::
{    
    Cola espera 
    int idP
    do Persona[*]?llegue(idP) -> push(espera, idP)
    □ (not empty(espera)), Empleado?pedido() -> Empleado!siguiente(pop(espera))
    od
}

Process Empleado::
{
    int idP
    while (true)
    {
        Administrador!pedido()
        Administrador?siguiente(idP)
        Persona[idP]!usarSimulador()
        Persona[idP]?liberarSimulador()
    }
}