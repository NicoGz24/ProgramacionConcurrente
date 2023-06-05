/*
En un sistema para acreditar carreras universitarias, hay UN Servidor que atiende pedidos
de U Usuarios de a uno a la vez y de acuerdo con el orden en que se hacen los pedidos.

Cada usuario trabaja en el documento a presentar, y luego lo envía al servidor; espera la
respuesta de este que le indica si está todo bien o hay algún error. Mientras haya algún error,
vuelve a trabajar con el documento y a enviarlo al servidor. 

Cuando el servidor le responde que está todo bien, el usuario se retira. Cuando un usuario envía un pedido espera a lo sumo
2 minutos a que sea recibido por el servidor, pasado ese tiempo espera un minuto y vuelve a
intentarlo (usando el mismo documento).
*/

procedure Universidad is

    Task Type Usuario;

    Task Servidor is
        Entry enviarDocumento(docu: IN text, ok: OUT bool );
    end Servidor;

    arrUsuarios: array(1..U) of Usuario;

    Task Body Usuario is
        documento: text;
        ok: bool := false;
    begin
        TrabajarDocumento(documento)
        while(not ok) loop
            SELECT 
                Servidor.enviarDocumento(documento,ok)
                if(not ok)then
                    TrabajarDocumento(documento)
                end if
            OR DELAY 120
                delay(60)
            end SELECT
        end loop;
    end Usuario;

    Task Body Servidor is
    begin
        loop
            accept enviarDocumento(docu: IN text, ok: OUT bool)do ok := Analizar(docu) end enviarDocumento;
        end loop;
    end Servidor;

begin
    null;
end Universidad