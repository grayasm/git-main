+---------------------------------------------------------------------------+
		ATOMIC OPERATIONS
+---------------------------------------------------------------------------+

int flag;
void add_head(struct List* list, struct Node* node)
{
	while(flag != 0)
		;
	flag = 1;
	node->next = list->head;
	list->head = node;
	flag = 0;
}
+---------------------------------------------------------------------------+
	and equivalent in ASM:
+---------------------------------------------------------------------------+

;		{
	xor eax, eax
$L86:
;			while(flag != 0)
	cmp DWORD PTR _flag, eax
	jne	SHORT $L86

;			flag = 1;
	mov eax, DWORD PTR _list$[esp-4]
	mov ecx, DWORD PTR _node$[esp-4]
	mov DWORD PTR _flag, 1

;			node->next = list->head;
	mov edx, DWORD PTR[eax]
	mov DWORD PTR [ecx], edx
	
;			list->head = node;
	mov DWORD PTR [eax], ecx
	
;			flag = 0;
	mov DWORD PTR _flag, 0

;		}
	ret 0	

+---------------------------------------------------------------------------+

	There are several ways that the routine as written could fail. It is 
	possible that a CONTEXT SWITCH could happen between the comparison on
	line 23 and the jump on line 24. Another thread could enter this routine
	even though this thread was about to set the flag.
	The routine could then fail if a context switch happened after lines 32
	or 33.
		An operation that will coplete without ever being interrupted is called
	an ATOMIC OPERATION. Checking and setting the flag in the example above
	must be an atomic operation. If it ever got interrupted, then it would
	create a race condition when it was trying to solve one.
		Checking and setting the flag is such a common operation that it is
	implemented in hardware on many processors. It is called TEST AND SET
	instruction. In practice, only the operating system will use the TEST AND SET
	instruction. The operating system provides high-level mechanisms that your
	program may use instead of TEST AND SET.
		
+---------------------------------------------------------------------------+	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	