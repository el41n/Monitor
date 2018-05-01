#include "bigclientcores.h"

BigClientCores::BigClientCores()
{

}

bool BigClientCores::mapArchitecture()
{
    this->setLeaf01H();
    if(extendedFamily == 0)
        {
          if(family == 0x6)
          {
              if(extendedModel == 0)
              {
                  switch (model) {
                  case 0x9:
                      setMicroArchitecture("Lakemount");
                      setCore("Quark");
                      break;
                  case 0x8:
                      setMicroArchitecture("P5");
                      setCore("P55C(Mobile)");
                      break;
                  case 0x7:
                      setMicroArchitecture("P5");
                      setCore("P55C(Mobile)");
                      break;
                  case 0x4:
                      setMicroArchitecture("P5");
                      setCore("P55C");
                      break;
                  case 0x2:
                      setMicroArchitecture("P5");
                      setCore("P54CS");
                      break;
                  case 0x1:
                      setMicroArchitecture("P5");
                      setCore("P54");
                      break;
                  default:
                      return false;
                      break;
                  }
              }
              if(extendedModel == 3)
              {
                  switch (model) {
                  case 0x5:
                      setMicroArchitecture("Lakemount");
                      setCore("Quark");
                      break;
                  case 0x6:
                      setMicroArchitecture("P5");
                      setCore("P55C(Mobile)");
                      break;
                  case 0xc:
                      setMicroArchitecture("Hasswell");
                      setCore("S");
                      return true;
                  case 0x4:
                      setMicroArchitecture("P5");
                      setCore("P55C");
                      break;
                  case 0x2:
                      setMicroArchitecture("P5");
                      setCore("P54CS");
                      break;
                  case 0x1:
                      setMicroArchitecture("P5");
                      setCore("P54");
                      break;
                  default:
                      return false;
                      break;
                  }
          } else return false;
        } else return false;
        return true;
}
}
