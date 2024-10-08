#include"event.h"

void MyEvent::Exceptions(MyException* pObjExcep){
  assert(pObjExcep != nullptr);
  pMyExcep = pObjExcep;
  switch(evCode){
    case 100 : {//wrong name
      msg = pObjExcep->GetWrongNames();
      wrongName.push_back(msg);
      break;
    }
    case 0 : {
      msg = "Stop!\n";
      break;
    }
  }
}

void MyEvent::SetEvent(const size_t ev){
  assert(this != nullptr);

  evCode = ev;
}

vector<string>& MyEvent::GetWrongNames(){
  return wrongName;
}

void MyEvent::Signal(){
  pServ->Signal(evCode);
}

void MyEvent::SetObjServ(Server* ptr){
  assert(ptr != nullptr);
  pServ = ptr;
}
