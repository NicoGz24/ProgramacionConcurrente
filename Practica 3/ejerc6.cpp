6. En una playa hay 5 equipos de 4 personas cada uno (en total son 20 personas donde cada
una conoce previamente a que equipo pertenece). Cuando las personas van llegando
esperan con los de su equipo hasta que el mismo esté completo (hayan llegado los 4
integrantes), a partir de ese momento el equipo comienza a jugar. El juego consiste en que
cada integrante del grupo junta 15 monedas de a una en una playa (las monedas pueden ser
de 1, 2 o 5 pesos) y se suman los montos de las 60 monedas conseguidas en el grupo. Al
finalizar cada persona debe conocer el monto total juntado por su grupo. Nota: maximizar
la concurrencia. Suponga que para simular la búsqueda de una moneda por parte de una
persona existe una función Moneda() que retorna el valor de la moneda encontrada.

process persona [id:0..19]{
    int idE = DarEquipo()
    int cantMonedas = 0
    int monto = 0
    bool gane = false
    Equipo[idE].formarEquipo()
    while(cantMonedas <= 15){
        monto =+ Moneda()
        cantMonedas++
        delay()
    }
    Playa.sumarMonto(idE,monto)
    Playa.ganador(gane, idE)
    if(gane){
        Festejar con equipo()
    }
}

Monitor Equipo[1..4]{
    cond esperarP
    cantP = 0

    procedure formarEquipo(){
        cantP++
        if(cantP == 4){
            signalAll(esperarP)
        }
        else{
            wait(esperarP)
        }
    }

Monitor Playa{
    int montosE[4]=([4],0)
    int equipos[4]=([4],0)
    int cantE = 0
    cond esperarE[4], esperar

    procedure sumarMontos(idE: in int, monto: in int){
        montosE[idE]=+monto
        equipos[idE]++
        if(equipos[idE] == 4){
            cantE++
            signalAll(esperar[idE])
        }
        else{
            wait(esperar[idE])
        }
    }

    procedure ganador(gane: out bool, idE: in int){
        int i, max = 0, id;
        if(cantE == 4){
            signallAll(esperar)
        }
        else{
            wait(esperar)
        }
        for i = 0 to 3 {
            if (max < montos[i]){
                max = montos[i]
                id = i
            }
        }
        if(id = idE)
            gane = true
    }
}
}