  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Claude DUFOURMONT Le 05/04/2022
  // claude.dufourmont@laposte.net
  // https://www.youtube.com/c/ClaudeDufourmont
  // Nouveau concept pour calculer la résistance série d'une LED, en prenant en compte une donnée supplémentaire : la perception de la luminosité par l'oeil humain
  // Ce code est associé à la vidéo YouTube : https://youtu.be/AS8kzdWavEM
  // Ce code est associé à Github :https://github.com/claudiusmarius/https-github.com-claudiusmarius-LED-CALCULATOR---NEW-CONCEPT/upload/main
  // https://pastebin.com/CZHDZ07r
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 
  #define BrocheDAC A0                  // Envoie signal ANA vers la base du transistor Q1
  #define potVariationSignal A4         // Curseur potentiomètre su A4
  #define BrocheVC A8                   // "Image"tension collecteur  sur A8
  #define BrocheVE A7                   // "Image"tension émetteur  sur A7
  #define BPRst 10                      // Bouton de rst
  
  int etatBPRst = LOW;
  
  int ValueDAC;                         // Echelle : 0 -> 1023 points (analogWriteResolution(10)) pour 0 -> 3.3V
  int a;                                // Curseur potentiomètre (varie de 0 à 3.3V pour 0 à 1023 points
  int aa;
  int R1 = 82;
  
  float ID1;                            // Variable courant LD calculé
  float VCC5 = 5.08;                    // Tension d'alimentation fournie par la prise USB (A MESURER ET ACTUALISER DANS LE CODE POUR UNE PLUS GRANDE PRECISION)
  float VCC3 = 3.32;                    // Tension d'alimentation fournie par le SEEEDUINO XIAO ((A MESURER ET ACTUALISER DANS LE CODE POUR UNE PLUS GRANDE PRECISION)
  float R3V;                            // Résistance calculée pour une tension de 3.3V
  float R5V;                            // Résistance calculée pour une tension de 5V
  float R10V;                           // Résistance calculée pour une tension de 10V
  float R12V;                           // Résistance calculée pour une tension de 12V
  float R15V;                           // Résistance calculée pour une tension de 15V
  
  int VCpoint;                          // Valeur de VC en points
  int VEpoint;                          // Valeur de VE en points
  
  float VC;                             // Valeur de VC en volts
  float VE;                             // Valeur de VE en volts
  float VD1;
  float k = .5;                         // Les valeurs analogiques pouvant atteindre 5V sont divisées par deux via un pont diviseur
  
  void setup() 
  {
  
  analogReadResolution(10);             // Spécification résolution à utiliser pour la lecture ANA
  analogWriteResolution(10);  
  pinMode (BPRst, INPUT_PULLUP);        // BPRst en entrée pull up
  ValueDAC = 0;                         // Initialisation à 0 de ValueDAC
  a = 0;                                // Initialisation à 0 de a (curseur potentiomètre
  aa = 0;
  Serial.begin(115200);                   // ¨Préparation de la liaison série à 9600 bauds

  }

  void loop() 
  {
  
  VCpoint = analogRead (A8);            // Lecture en points de VC (affecté du coefficient k)
  VEpoint = analogRead (A7);            // Lecture en points de VE (affecté du coefficient k)

  VC = VCC3 *VCpoint / 1023 /k ;        // Calcul de VC en volts
  VE = VCC3 *VEpoint / 1023 /k ;        // Calcul de VE en volts
  
  VD1 = VCC5 - VC;                      // Calcul de VD1 en volts
  ID1 = 1000*VE/R1;                     // Calcul de ID1 en mA         

  R3V = (3.3 - VD1) / ID1;              // Calcul de la résistance LED pour une tension de 3.3V
  R5V = (5 - VD1) / ID1;                // Calcul de la résistance LED pour une tension de 5V
  R10V = (10 - VD1) / ID1;              // Calcul de la résistance LED pour une tension de 10V
  R12V = (12 - VD1) / ID1;              // Calcul de la résistance LED pour une tension de 12V
  R15V = (15 - VD1) / ID1;              // Calcul de la résistance LED pour une tension de 15V
  
  a = analogRead (potVariationSignal);  // Lecture en points de la tension curseur du potentiomètre

  
  // *********************** Type de réglage à choisir *******************************************************
  // *********************************************************************************************************
  
     //ValueDAC = a;                       // Reglage grossier
  
     //ValueDAC = map(a,0,1023, 220,500);
     //ValueDAC = map(a,0,1023, 220,600); 
     //ValueDAC = map(a,0,1023, 230,750); 
      
      ValueDAC = map(a,0,1023, 190,800);

  // ====================================================================================================================
  // Les lignes ci-dessus servent à déterminer la plage de de réglage, elles peuvent être modifiées selon vos préférences
  // ====================================================================================================================
  
  // ********************************************************************************************************
  // ********************************************************************************************************
  
  if ( (abs (aa - a)) >4 )
  {
  
  analogWrite(BrocheDAC, ValueDAC);     // Positionnement de la dernière ValueDAC sur son port
  delay(5);
  Serial.println (" ");
  Serial.println (" ");
  Serial.println (" ");
  Serial.println (" ");
  Serial.println (" ");
  Serial.println ("    ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- ");
  Serial.println (" ");
  Serial.println ("                                                                      LED");
  Serial.println ("                                                                  CALCULATOR ");
  Serial.println ("                                                                CLAUDE DUFOURMONT ");
  Serial.println ("                                                          claude.dufourmont@laposte.net");
  Serial.println (" ");
  Serial.println ("                                    visitez ma chaîne YouTube :  --->  https://www.youtube.com/c/ClaudeDufourmont ");
  Serial.println (" ");
  Serial.println ("                                             LIKEZ    -    SOUSCRIVEZ    -    PARTAGEZ    -    COMMENTEZ ");
  Serial.println (" ");
  Serial.println ("                              Ce montage a pour rôle de déterminer la résistance à placer en série avec une LED ");
  Serial.println ("                              Après avoir déterminé le niveau de luminosité souhaité ");
  Serial.println ("                              Ce niveau de luminosité est réglé à partir du potentiomètre ");
  Serial.println ("                              Les valeurs de résistance sont données pour différentes valeurs de tension");
  Serial.println (" ");
  Serial.println ("    ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- ");
  Serial.println ("    ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- ");
  Serial.println ("");
  Serial.println ("");
  Serial.println ("");
  Serial.print ("            VC (V) =           ");
  Serial.print (VC);
  Serial.println ("    Tension collecteur Transistor ");
  Serial.print ("            VE (V) =           ");
  Serial.print (VE);
  Serial.println ("    Tension Emetteur Transistor ");
  Serial.print ("            VD1 (V) =          ");
  Serial.print (VD1);
  Serial.println ("    Tension de seuil D1");
  Serial.print ("            ID1 (mA) =         ");
  Serial.print (ID1);
  Serial.println ("    Courant D1 ");
  Serial.print ("            R3V (Kohms) =      ");
  Serial.print (R3V);
  Serial.println ("    Valeur de résistance à placer en série avec la LED si le circuit R+LED est alimenté en 3.3V");
  Serial.print ("            R5V (Kohms) =      ");
  Serial.print (R5V);
  Serial.println ("    Valeur de résistance à placer en série avec la LED si le circuit R+LED est alimenté en 5V");
  Serial.print ("            R10V (Kohms) =     ");
  Serial.print (R10V);
  Serial.println ("    Valeur de résistance à placer en série avec la LED si le circuit R+LED est alimenté en 10V");
  Serial.print ("            R12V (Kohms) =     ");
  Serial.print (R12V);
  Serial.println ("    Valeur de résistance à placer en série avec la LED si le circuit R+LED est alimenté en 12V");
  Serial.print ("            R15V (Kohms) =     ");
  Serial.print (R15V);
  Serial.println ("    Valeur de résistance à placer en série avec la LED si le circuit R+LED est alimenté en 15V");
  Serial.println (" ");
  Serial.println (" ");
  Serial.println (" ");
  Serial.println ("    ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- ");
  Serial.println (" ");
  aa = a;
  }
  
  digitalRead (BPRst);                  // Lecture de l'entrée numérique affectée à BPRst
  if (digitalRead (BPRst) == LOW)       
  {
  etatBPRst = HIGH;                     // Détermination de son état
  }
  if (etatBPRst == HIGH)
  {
  NVIC_SystemReset();                   // RST logicielle si etatBPRst == HIGH
  etatBPRst = LOW;                      // Remise à LOW de létatBPRst
  }
   
  }
  

 
