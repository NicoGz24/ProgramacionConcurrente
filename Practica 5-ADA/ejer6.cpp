/*
En una playa hay 5 equipos de 4 personas cada uno (en total son 20 personas donde cada
una conoce previamente a que equipo pertenece). Cuando las personas van llegando
esperan con los de su equipo hasta que el mismo esté completo (hayan llegado los 4
integrantes), a partir de ese momento el equipo comienza a jugar. 

El juego consiste en que cada integrante del grupo junta 15 monedas de a una en una playa 
(las monedas pueden ser de 1, 2 o 5 pesos) y se suman los montos de las 60 monedas conseguidas en el grupo. 

Al finalizar cada persona debe conocer el grupo que más dinero junto. Nota: maximizar la
concurrencia. Suponga que para simular la búsqueda de una moneda por parte de una
persona existe una función Moneda() que retorna el valor de la moneda encontrada.
*/

procedure playa is

    Task Type Equipos is
        Entry sumarMonedas(cantidad: IN integer);
        Entry despertarJugadores()
    end Equipo;

    Task Type Persona is
        Entry identificar(pos: IN integer);
        Entry jugar();
        Entry ganador();
    end Persona;

    Task Coordinador is
        Entry llegada(equipo,id: IN integer);
        Entry equipoTermino(equipo,total: IN integer);
    end Coordinador;

    arrPersonas: array(1..20) of Persona;
    arrEquipos: array(1..5) of Equipo

    Task Body Persona is
        equipo,id: integer
        m: Moneda;
        total: integer :=0;
        aux: integer;
    begin
        accept  identificar(pos: IN integer) do id := pos end identificar;
        equipo:=MiEquipo()
        Coordinador.llegada(equipo,id);
        accept jugar();
        for i:=0 to 14 do
            m:=juntarMoneda()
            total:= total + Moneda(m);
        end for;
        Equipo[equipo].sumarMonedas(total);
        accept ganador(aux);
        if (aux = equipo)then
            festejar()
        end if
    end Persona;

    Task Body Equipo is 
        total, integrantes: integer :=0;
        idJugadores:array(0..3) of integer; //si el jugador conoce a su equipo, el equipo conoce a sus jugadores
    begin
        loop
            SELECT 
                accept sumarMonedas(cantidad: IN integer) do 
                    total:=total + cantidad; 
                    integrantes:=integrantes + 1 
                end sumarMonedas;
                if (integrantes = 4)then
                    Coordinador.equipoTermino(id, total);
                end if
            OR 
                accept despertarJugadores() do
                    for i:=0 to 3 do
                        Persona[idJugadores[i]].jugar();
                    end for
                end despertarJugadores;
        end loop
    end Equipo;

    Task Body Coordinador is 
        arreglo: array(1..5) of integer;
        equiposT: array(1..5) of integer;
        terminados: integer := 0;
        ganador: integer;
    begin
        loop
            SELECT 
                accept llegada(equipo,id: IN integer) do 
                    arreglo[equipo]:=arreglo[equipo]+1;
                    if(arreglo[equipo] = 4) then
                        Equipos[equipo].despertarJugadores();
            OR
               accept equipoTermino(equipo,total: IN integer)do
                    equiposT[equipo]:=total;
               end equipoTermino;
               terminados := terminados +1;
               if(terminados = 5) then
                    ganador := buscarMax(equiposT);
                    for i:=1 to 20 do
                        Persona[i].ganador(ganador);
                    end for
                end if
            end SELECT
        end loop
    end Coordinador;

begin
    for i:=1 to 20 do  
        Personas[i].identificar(i);
    end for; 
end playa;