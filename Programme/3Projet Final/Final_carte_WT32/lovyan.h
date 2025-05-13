#ifndef LOVYAN_H
#define LOVYAN_H

// BIBLIOTHEQUE
#include <LovyanGFX.hpp>

// Classe LGFX
class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ST7796 _panel;
  lgfx::Bus_Parallel8 _bus;
  lgfx::Touch_FT5x06 _touch;

  public:
    LGFX();                                 // constructeur
    void initTouch();                       // initialise le tactile
    bool getTouch(int16_t* x, int16_t* y);  // récupère une position tactile
    void initialiser();                     
};

// Déclaration externe de l'objet lcd
extern LGFX lcd; 

#endif