#pragma once

// ΩÃ±€≈Ê ∏≈≈©∑Œ
#define SINGLE(type)	public:\
							static type* GetInst()\
							{\
								static type mgr;\
								return &mgr;\
							}\
						private:\
							type();\
							~type();