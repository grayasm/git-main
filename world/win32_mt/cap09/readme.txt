+------------------------------------------------------------------------------+
	Using C++
+------------------------------------------------------------------------------+
	Implemented class thread with member:
		static DWORD WINAPI ThreadFunc(LPVOID n) {
			thread* _this = (thread*) n;
			_this->Run(); 
		};
		
	Implemented classes:
	CriticalSection with: ctor(), ~dtor(), void Enter(), void Leave();
	Lock with: Lock(CriticalSection* pCS), ~dtor()
	LockableObject with: ctor(), ~dtor(), Lock()=0; Unlock()=0;
+------------------------------------------------------------------------------+