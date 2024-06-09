oid init_display(int argc, char *argv[])
{
    Widget test, restart, stop;

    //génération des bouttons utilisateur
    test = MakeButton("Tester", test_callback, NULL);  //initialisation boutton tester
    restart = MakeButton("Recommencer", restart_callback, NULL); //initialisation boutton recoomencer
    stop = MakeButton("Arrêter", stop_callback, NULL); //initialisation boutton arrêter

    SetWidgetPos(stop, PLACE_RIGHT, NULL, PLACE_ABOVE, NULL); //positionnement bouton stop
    SetWidgetPos(test, PLACE_LEFT, NULL, PLACE_ABOVE, NULL); //positionnement bouton test
    SetWidgetPos(restart, PLACE_CENTER, NULL, PLACE_ABOVE, NULL); //positionnement bouton restart

    //génération de l'espace textuel
    zone_text = MakeTextWidget(NULL, 20, 100, TRUE); // initialisation zone textuelle
    SetWidgetPos(zone_text, PLACE_ABOVE, NULL, NO_CARE, NULL); //positionnement de la zone de text

}
//Rôle : crée une box orange avec la lettre à l'intérieur 
void box_orangeDef(char p*, char l,...){
    Widget orange,label; //crée un widget nomé "nom"
    orange = MakeColorBox(GetRGBColor(255, 0, 0), 100, 100);    // Red box
    label = MakeLabel(l); //insertion de la lettre dans la case

    //Positionnement des éléments créés
    SetWidgetPos(orange, PLACE_UNDER, NULL, NO_CARE, NULL);
    SetWidgetPos(label, PLACE_UNDER, orange, NO_CARE, NULL);

}

//Rôle : crée une box orange avec la lettre à l'intérieur 
void box_bleuDef(char p*, char l,...){
    Widget bleu,label; //crée un widget nomé "nom"
    bleu = MakeColorBox(GetRGBColor(255, 0, 0), 100, 100);    // Red box
    label = MakeLabel(l); //insertion de la lettre dans la case

    //Positionnement des éléments créés
    SetWidgetPos(bleu, PLACE_UNDER, NULL, NO_CARE, NULL);
    SetWidgetPos(label, PLACE_UNDER, bleu, NO_CARE, NULL);
}

//Rôle : crée une box orange avec la lettre à l'intérieur 
void box_rougeDef(char p*, char l,...){
    Widget rouge,label; //crée un widget nomé "nom"
    rouge = MakeColorBox(GetRGBColor(255, 0, 0), 100, 100);    // Red box
    label = MakeLabel(l); //insertion de la lettre dans la case

    //Positionnement des éléments créés
    SetWidgetPos(rouge, PLACE_UNDER, NULL, NO_CARE, NULL);
    SetWidgetPos(label, PLACE_UNDER, rouge, NO_CARE, NULL);
}


void GenereBoxDisp(...){
    //fait appels aux trois fonction de création de box 
    //cette fonction prend en param le résultat du test du mot que l'utilisateur a entré ainsi qu'une position matricielle (1,1) ou (4,5)
    //conseil : utiliser des switch 
}
