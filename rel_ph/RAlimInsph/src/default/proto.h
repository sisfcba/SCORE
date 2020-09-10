
/* ../Callbacks.cc */
int StartPrincipal ( PtWidget_t *link_instance , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );
int Pagina ( PtWidget_t *widget , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );
int Timer ( PtWidget_t *widget , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );
int Grupo ( PtWidget_t *widget , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );
int Sair ( PtWidget_t *widget , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );

/* ../RAlimInsPH.cc */
int ini_rel ( int argc , char *argv []);

/* ../abmain.cc */
int main ( int argc , char *argv []);

/* ../Funcs.cc */
void ExibeTela ( t_widgets &aWidgets , short int aGrupo , short int &aPos );
void MontaTela ( t_widgets &aWidgets , t_alarmePH *apAlarme , t_cnf_alarme &aCnfAla , short int aGrupo );
void MontaLinha ( t_widgets &aWidgets , short int aLinha , short int aIndCuba );
void TrataAlarmeIns ( t_widgets &aWidgets , t_alarmePH *apAlarme , t_cnf_alarme &aCnfAla , short int aLinha , short int aIndCuba );
char *SinalSituacaoAlim ( short int aIndCuba );
char *SinalSituacao ( int aIndCuba );
void SetaLimitesScroll ( PtWidget_t *apWidget , short int aGrupo );
void PegaWidgets ( t_widgets &aWidgets );
int LeTabelas ( void );
char *LeComum ( char *apNome , size_t aTamanho );
