from z3 import *

s = z3.Solver()

eax_in = z3.BitVec("eax_in", 32)
ecx_in = z3.BitVec("ecx_in", 32)
eax1, eax2, eax3 = z3.BitVecs("eax1 eax2 eax3", 32)
edx1, edx2 = z3.BitVecs("edx1 edx2", 32)

model = [
    eax1 == eax_in + ecx_in,
    eax2 == eax1 << z3.BitVecVal(12, 32),
    eax3 == eax2 * ecx_in,
    edx1 == eax3,
    edx2 == edx1 ^ ecx_in
]

s.add(model)

if s.check() == z3.unsat:
    print('Cannot find solution!')
    sys.exit(-1)

requirement = edx2 == z3.BitVecVal(0x100, 32)
s.add(requirement)

#requirement = eax_in == z3.BitVecVal(0x0003ff01, 32)
#s.add(requirement)

if s.check() == z3.sat:
    print(f'Found a solution for {requirement}')
    m = s.model()

    eax_val = m[eax_in].as_long()
    ecx_val = m[ecx_in].as_long()
    
    print(f'EAX : 0x{eax_val:02x}, ECX : 0x{ecx_val:02x}')
else:
    print('Cannot solve!')

solutions = [('eax_in', 'ecx_in')]
while s.check() == z3.sat:
    # every new solution = new model
    m = s.model()

    eax_val = int(f'{m[eax_in]}')
    ecx_val = int(f'{m[ecx_in]}')
    

    r_eax = eax_in != m[eax_in]
    r_ecx = ecx_in != m[ecx_in]
    s.add(r_eax)
    s.add(r_ecx)

    solutions.append((m[eax_in], m[ecx_in]))
    print(f'EAX : 0x{eax_val:02x}, ECX : 0x{ecx_val:02x}')


    if len(solutions) > 10:
        break