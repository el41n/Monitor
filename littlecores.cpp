#include "littlecores.h"

LittleCores::LittleCores()
{

}

bool LittleCores::mapArchitecture()
{
    if(extendedFamily == 0)
    {
      if(family == 0x6)
      {
          if(extendedModel == 0x1)
          {
              if(model == 0xc)
              {
                  setMicroArchitecture("Bonnel");
                  setCore("Silverthorne");
                  return true;
              }
          }
          if(extendedModel == 0x2)
          {
              switch (model)
              {
              case 0x6:
                  setMicroArchitecture("Bonnel");
                  setCore("Lincroft");
                  return true;
              case 0x7:
                  setMicroArchitecture("Saltwell");
                  setCore("Penwell");
                  return true;
              default:
                  break;
              }
          }
          if(extendedModel == 0x3)
          {
              switch (model)
              {
              case 0x5:
                  setMicroArchitecture("Saltwell");
                  setCore("Cloverview");
                  return true;
              case 0x6:
                  setMicroArchitecture("Saltwell");
                  setCore("Cedarview");
                  return true;
              case 0x7:
                  setMicroArchitecture("Silvermont");
                  setCore("Bay Trail");
                  return true;
              default:
                  break;
              }
          }
          if(extendedModel == 0x4)
          {
              switch (model)
              {
              case 0xa:
                  setMicroArchitecture("Silvermont");
                  setCore("Tangier");
                  return true;
              case 0xd:
                  setMicroArchitecture("Silvermont");
                  setCore("Avoton");
                  return true;
              case 0xc:
                  setMicroArchitecture("Airmont");
                  setCore("Braswell");
                  return true;
              default:
                  break;
              }
          }
          if(extendedModel == 0x5)
          {
              switch (model)
              {
              case 0xa:
                  setMicroArchitecture("Silvermont");
                  setCore("Anniedale");
                  return true;
              case 0xd:
                  setMicroArchitecture("Silvermont");
                  setCore("SoFIA");
                  return true;
              case 0xc:
                  setMicroArchitecture("Goldmont");
                  setCore("Apollo Lake");
                  return true;
              case 0xf:
                  setMicroArchitecture("Goldmont");
                  setCore("Denverton");
                  return true;
              default:
                  break;
              }
          }
          if(extendedModel == 0x7)
          {
              switch (model)
              {
              case 0xa:
                  setMicroArchitecture("Goldmont Plus");
                  setCore("Gemini Lake");
                  return true;
              default:
                  break;
              }
          }
      }
    }
    return false;
}
