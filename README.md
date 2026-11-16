# Hospital Patient Management System (C)

A menu-driven console program to manage admitted hospital patients using a **singly linked list**. Records are saved to a file so they persist between runs.

## Features
- Admit a patient (ID, name, age, disease, doctor)
- Display all patients with a total count
- Search a patient by ID
- Update disease, doctor and days admitted
- Discharge a patient and print the bill (days x daily room charge)
- Prevents duplicate patient IDs
- Saves to `patients.dat` on exit and loads it on start

## Concepts used
Structures, pointers, dynamic memory (`malloc` / `free`), linked list (insert at end, search, delete), binary file handling

## How to run
```bash
gcc hospital.c -o hospital
./hospital
```
On Windows (MinGW): `gcc hospital.c -o hospital.exe` then `hospital.exe`

## Sample session
```
--- Hospital Patient Management ---
Choice: 1
Patient ID: 101
Name: Ravi Kumar
Age: 45
Disease: Fever
Doctor assigned: Dr. Meena
Patient admitted.
```

## Future improvements
- Add gender, ward number and admission date
- Search by name
- Keep a separate list of discharged patients
