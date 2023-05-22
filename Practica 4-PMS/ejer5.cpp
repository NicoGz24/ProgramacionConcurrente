En un estadio de fútbol hay una máquina expendedora de gaseosas que debe ser usada por
E Espectadores de acuerdo al orden de llegada. Cuando el espectador accede a la máquina
en su turno usa la máquina y luego se retira para dejar al siguiente. Nota: cada Espectador
una sólo una vez la máquina.

Process Espectador [id: 0 to E-1]
{
    Admin!llegue(id)
    Admin!pedido()
    Admin?miTurno()
    UsarMaquina()
    Admin!siguiente()
}

Process Admin::
{
    Cola cola
    int idE
    bool libre = true
    do Espectador[*]?llegue(idE) -> push(cola,idE)
    □ libre && (not empty(cola)) Espectador[*]?pedido() -> pop(cola,idE),  Espectador[idE]!miTurno(), libre = false
    □ Espectador[*]?siguiente() -> libre = true
    od
}
