/* -- Calcula Provável Quebra sem Sinalização -- */
if ( EST_AVC(Cuba).EfeitoQueb eq FALSO and
        EST_AVC(Cuba).EfeitoCorr eq FALSO and
        //(HoraAtualCtrl-AvcLocal[Cuba].HoraUltProvQueb) > AvcLocal[Cuba].TEfeitoProvQueb))
        (HoraAtualCtrl-AvcLocal[Cuba].HoraUltProvQueb) > 1800L and
        ((BuffSize>=5) and (BuffSize<=30)) and
        ((HoraAtualCtrl-AVC.Cleit[Cuba].HoraInicDesLeit) > (30*60L)))
{		
    //HistDerivH array circular shifting: HistDerivH[Last] to HistDerivH[Last-1]
    memmove(&AvcLocal[Cuba].HistDerivH[0],&AvcLocal[Cuba].HistDerivH[1],
        (sizeof(AvcLocal[Cuba].HistDerivH)-sizeof(AvcLocal[Cuba].HistDerivH[0])));

    //RSuaveDerivH to HistDerivH[Last]
    AvcLocal[Cuba].HistDerivH[BuffSize-1] = AVC.Ea[Cuba].RSuaveDerivH;
    
    if(AvcLocal[Cuba].ContHistDerivH < BuffSize)
        AvcLocal[Cuba].ContHistDerivH++;

    /* Calcula coeficiente angular de RSuaveDerivH */
    if( AvcLocal[Cuba].ContHistDerivH >= BuffSize)
    {
        i = 0;
        sumx = 0;
        sumx2 = 0;
        sumy = 0;
        sumy2 = 0;
        sumxy = 0;

        for (i=0;(i+(BuffSize-AvcLocal[Cuba].ContHistDerivH))<BuffSize;++i)
        {
            k = i+(BuffSize-AvcLocal[Cuba].ContHistDerivH); 
            x[i]= i*1;
            sumx += x[i];  
            sumx2 += x[i]*x[i]; 
            sumy += AvcLocal[Cuba].HistDerivH[k];
            sumy2 += AvcLocal[Cuba].HistDerivH[k]*AvcLocal[Cuba].HistDerivH[k]; 
            sumxy += x[i]*AvcLocal[Cuba].HistDerivH[k];
        }
                
        AVC.User1[Cuba].CoefAngDeriv = ((AvcLocal[Cuba].ContHistDerivH*sumxy) - (sumx*sumy))/
            ((AvcLocal[Cuba].ContHistDerivH*sumx2) - (sumx*sumx));

        if (EST_AVC(Cuba).Est.QuebPrev eq VERDADEIRO)
            strcpy(Par3,"QuebPrev");
        else if (EST_AVC(Cuba).EaPrev eq VERDADEIRO)
            strcpy(Par3,"EaPrev  ");
        else if (EST_AVC(Cuba).Est.DerBaixa eq VERDADEIRO)
            strcpy(Par3,"DerBaixa");

        if (AVC.User1[Cuba].CoefAngDeriv < AVC.ParUser1[Cuba].NivelProvQueb)
        {
            AvcLocal[Cuba].IntervQueb = (long)((HoraAtualCtrl - AVC.User2[Cuba].HoraEvQuebrada)/60L);
            MontaHoraMin((long)AVC.Cleit[Cuba].TUltEa/60L, Par1, "%03d:%02d"); //Tempo em min desde Ult. EA
            MontaHoraMin((HoraAtualCtrl-(BuffSize*2*60))/60L, Par2, "%02dh%02dm"); //Hora da Prov Queb
            GeraEvento(EV_PROVQUEB,Cuba,-1,	AvcLocal[Cuba].IntervQueb,Par3,Par1,Par2);
            AvcLocal[Cuba].HoraUltProvQueb = HoraAtualCtrl;
        }
    }		
}	
else
{ //Zerar buffer da derivada histórica quando em quebrada e corrida
    
    strcpy(Par3,"--------");
    AvcLocal[Cuba].ContHistDerivH = 0;
    for(i=0;i<30;i++)
        AvcLocal[Cuba].HistDerivH[i]=0.0;
    
}