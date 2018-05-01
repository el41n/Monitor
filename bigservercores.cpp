#include "bigservercores.h"

BigServerCores::BigServerCores()
{

}

bool BigServerCores::mapArchitecture()
{
    if(extendedFamily == 0)
    {
      if(family == 0x6)
      {
          if(extendedModel == 0x0)
          {
              if(model == 0xa)
              {
                  setMicroArchitecture("P6");
                  setCore("P6");
                  return true;
              }
          }
          if(extendedModel == 0x1)
          {
              switch (model)
              {
              case 0x7:
                  setMicroArchitecture("Penryn(Server)");
                  setCore("Harpertown");
                  return true;
              case 0xd:
                  setMicroArchitecture("Penryn(Server)");
                  setCore("Dunnington");
                  return true;
              case 0xa:
                  setMicroArchitecture("Nehalem(Server)");
                  setCore("Bloomfield");
                  return true;
              case 0xe:
                  setMicroArchitecture("Nehalem(Server)");
                  setCore("Lynnfield");
                  return true;
              default:
                  break;
              }
          }
          if(extendedModel == 0x2)
          {
              switch (model)
              {
              case 0x5:
                  setMicroArchitecture("Nehalem(Server)");
                  setCore("EX");
                  return true;
              case 0x6:
                  setMicroArchitecture("Westmere(Server)");
                  setCore("EX");
                  return true;
              case 0x7:
                  setMicroArchitecture("Westmere(Server)");
                  setCore("Gulftown");
                  return true;
              case 0x7:
                  setMicroArchitecture("Sandy Bridge(Server)");
                  setCore("E");
                  return true;
              default:
                  break;
              }
          }
          if(extendedModel == 0x3)
          {
              switch (model)
              {
              case 0xe:
                  setMicroArchitecture("Ivy Bridge(Server)");
                  setCore("E");
                  return true;
              case 0xf:
                  setMicroArchitecture("Haswell (Server)");
                  setCore("E");
                  return true;
              default:
                  break;
              }
          }
          if(extendedModel == 0x4)
          {
              if(model == 0xf)
              {
                  setMicroArchitecture("Broadwell (Server)");
                  setCore("E");
                  return true;
              }
          }
          if(extendedModel == 0x5)
          {
              switch (model)
              {
              case 0x6:
                  setMicroArchitecture("Broadwell (Server)");
                  setCore("DE");
                  return true;
              case 0x5:
                  setMicroArchitecture("Skylake (Server)");
                  setCore("SP");
                  return true;
              default:
                  break;
              }
          } else return false;
      } else return false;
    } else return false;
    return true;
}
