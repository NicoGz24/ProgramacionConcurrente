/* 
En una clínica existe un médico de guardia que recibe continuamente peticiones de
atención de las E enfermeras que trabajan en su piso y de las P personas que llegan a la
clínica ser atendidos.

Cuando una persona necesita que la atiendan espera a lo sumo 5 minutos a que el médico lo
haga, si pasado ese tiempo no lo hace, espera 10 minutos y vuelve a requerir la atención del
médico. Si no es atendida tres veces, se enoja y se retira de la clínica.

Cuando una enfermera requiere la atención del médico, si este no lo atiende inmediatamente
le hace una nota y se la deja en el consultorio para que esta resuelva su pedido en el
momento que pueda (el pedido puede ser que el médico le firme algún papel). Cuando la
petición ha sido recibida por el médico o la nota ha sido dejada en el escritorio, continúa
trabajando y haciendo más peticiones.

El médico atiende los pedidos dándole prioridad a los enfermos que llegan para ser atendidos.
Cuando atiende un pedido, recibe la solicitud y la procesa durante un cierto tiempo. Cuando
está libre aprovecha a procesar las notas dejadas por las enfermeras.
*/

procedure Clinica is

    Task Medico is
        Entry solicitudE();
        Entry solicitudP();
        Entry notasE(nota: IN text);
    end Medico

    Task Type Enfermera;

    Task Type Persona;

    Task Escritorio is
        Entry dejarNota(nota: IN text)
    end Escritorio;

    arrEnfermeras: array(1..E) of Enfermera
    arrPersonas: array(1..P) of Personas

    Task body Escritorio is
        pedidosEspera: colaOrdenada
        notaAux:text
    begin
        loop    
            SELECT
                accept dejarNota(nota: IN text) do Agregar(pedidosEspera,nota) end dejarNota
            ELSE
                if(not empty(pedidosEspera))then
                begin
                    pop(pedidosEspera,notaAux);
                    Medico.notasE(notaAux);
                end if    
        end loop
    end

    Task Body Medico is
    begin
        loop
            SELECT 
                when(solicitudP`count = 0) => accept solicitudE();
                AtenderPedido()
                delay(x)
            OR 
                accept solicitudP();
                AtenderPedido(p);
                delay(x)
            OR 
                when(solicitudE`count = 0) and (solicitudP`count = 0) => accept notasE(nota: IN text) do procesarNota(nota) end notasE;   
            end SELECT
        end loop
    end Medico

    Task Body Enfermera is
        nota: text;
    begin
        loop 
            SELECT 
                Medico.solicitudE();
            ELSE
                EscribirNota(nota); 
                Escritorio.dejarNota(nota);
        end loop
    end Enfermera

    Task Body Persona is
        atendido: bool := false
        i: integer := 0
    begin
        while (i < 3) and (not atendido) loop
        begin
            SELECT 
                Medico.solicitudP();
                atendido := true;
            OR DELAY 300
                delay(600) //espera 10 minutos
                SELECT
                    Medico.solicitudP();
                    atendido := true;
                ELSE
                    null
                end SELECT
            end SELECT
            i:=i + 1;
        end loop
        if(not atendido)then
            IrseEnojado()
    end Persona
begin
    null;
end Clinica