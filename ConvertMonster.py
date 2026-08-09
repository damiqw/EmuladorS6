import os

def convert_txt_to_xml(input_file, output_file):
    fields = [
        "Index", "Rate", "Name", "Level", "Life", "Mana", "DamageMin", "DamageMax",
        "Defense", "MagicDefense", "AttackRate", "DefenseRate", "MoveRange", "AttackType",
        "AttackRange", "ViewRange", "MoveSpeed", "AttackSpeed", "RegenTime", "Attribute",
        "ItemRate", "MoneyRate", "MaxItemLevel", "MonsterSkill", "Resistance0", "Resistance1",
        "Resistance2", "Resistance3", "ElementalAttribute", "ElementalPattern", "ElementalDefense",
        "ElementalDamageMin", "ElementalDamageMax", "ElementalAttackRate", "ElementalDefenseRate"
    ]

    try:
        with open(input_file, 'r', encoding='utf-8') as f:
            lines = f.readlines()
    except FileNotFoundError:
        print(f"Error: No se encontro {input_file}")
        return

    with open(output_file, 'w', encoding='utf-8') as xml:
        xml.write('<?xml version="1.0" encoding="utf-8"?>\n')
        xml.write('<MonsterList>\n')

        for line in lines:
            line = line.strip()
            
            # Ignorar comentarios y lineas vacias
            if not line or line.startswith('//'):
                continue
            
            # Terminar de leer si encontramos 'end'
            if line.lower() == 'end':
                break
                
            # Separar considerando que el nombre (Name) puede tener comillas
            # Una forma simple es usar split y rearmar, pero vamos a hacerlo robusto
            # usando el modulo shlex o parseando manualmente
            import shlex
            try:
                tokens = shlex.split(line)
            except ValueError:
                # Fallback simple si falla shlex por comillas mal cerradas
                tokens = line.replace('"', '').split()
            
            if len(tokens) < 28:
                continue # No tiene suficientes tokens validos

            xml.write('    <Monster ')
            for i, token in enumerate(tokens):
                if i < len(fields):
                    xml.write(f'{fields[i]}="{token}" ')
            xml.write('/>\n')

        xml.write('</MonsterList>\n')
        
    print(f"Conversion exitosa: {output_file} ha sido creado.")

if __name__ == "__main__":
    # Ajusta estas rutas si es necesario
    input_path = input("Introduce la ruta de tu Monster.txt (Ej: D:\\Mu\\Monster.txt): ").strip()
    if input_path.startswith('"') and input_path.endswith('"'):
        input_path = input_path[1:-1]
        
    output_path = os.path.splitext(input_path)[0] + ".xml"
    
    convert_txt_to_xml(input_path, output_path)
    input("Presiona Enter para salir...")
