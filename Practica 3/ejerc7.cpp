7. Se debe simular una maratón con C corredores donde en la llegada hay UNA máquinas
expendedoras de agua con capacidad para 20 botellas. Además existe un repositor
encargado de reponer las botellas de la máquina. Cuando los C corredores han llegado al
inicio comienza la carrera. Cuando un corredor termina la carrera se dirigen a la máquina
expendedora, espera su turno (respetando el orden de llegada), saca una botella y se retira. Si
encuentra la máquina sin botellas, le avisa al repositor para que cargue nuevamente la
máquina con 20 botellas; espera a que se haga la recarga; saca una botella y se retira. Nota:
maximizar la concurrencia; mientras se reponen las botellas se debe permitir que otros
corredores se encolen.


process Ccorredor [id: 0..C-1]{
    Botella botella
    Carrera.inicio()
    CorrerCarrera()
    delay()
    Expendedora.retirarBotella(botella)
}

process repositor::{
    while(true){
       Expendedora.reponer()
    }

}

Monitor Carrera{
    int C = cantidadCorredores()
    int cantC = 0
    cond esperarC

    procedure inicio(){
        cantC++
        if(cantC == C){
            signalAll(esperarC)
        }
        else{
            wait(esperarC)
        }
    }
}

Monitor Expendedora{
    int cantC = 0
    int cantBotellas = 20
    bool libre
    cond esperar, repositor, sinBotellas

    procedure retirarBotella(botella: out Botella){
        cant++
        if(!libre){
            wait(esperar)
        }
        else{
            libre = false
        }
        if(cantBotellas == 0){
            signal(repositor)
            wait(sinBotellas)
        }
        cantBotellas--
        botella = SacarBotella()
        if(cantC > 0){
            cantC--
            signal(esperar)
        }
        else{
            libre=true
        }
    }

    procedure reponer(){
        if(cantBotellas > 0){
            wait(repositor)
        }
        cantBotellas = 20
        signal(sinBotellas)
    }

}