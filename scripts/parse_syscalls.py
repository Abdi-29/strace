import requests
import re

# URL of the syscall table (update this if the URL changes)
url = "https://raw.githubusercontent.com/vsteffen/ft_strace/master/includes/syscall_tables/syscall64.h"

# Fetch the contents of the file
response = requests.get(url)
syscall_lines = response.text.splitlines()

syscall_pattern = re.compile(
    r'\[\s*(\d+)\s*\] = \{"(\w+)", \{(.*?)\}, &(\w+)\},?')

syscall_entries = []

for line in syscall_lines:
    match = syscall_pattern.match(line)
    if match:
        number = int(match.group(1))
        name = match.group(2)
        args = match.group(3).split(', ')
        handler = match.group(4)
        syscall_entries.append((number, name, args, handler))

with open("syscall_table.c", "w") as f:
    f.write("#include <stddef.h>\n")
    f.write("#include \"syscalls.h\"\n")
    f.write("\n")
    f.write("static const t_syscall_entry syscall_table[] = {\n")
    
    for number, name, args, handler in syscall_entries:
        arg_types_str = ', '.join(args)
        f.write(f"    [{number}] = {{.number = {number}, .name = \"{name}\", .arg_types = {{{arg_types_str}}}, .handler = {handler}}},\n")
    
    f.write("};\n")
    f.write("\n")
    f.write("const t_syscall_entry *get_syscall_entry(int syscall_number) {\n")
    f.write("    if (syscall_number < 0 || syscall_number >= sizeof(syscall_table) / sizeof(syscall_table[0])) {\n")
    f.write("        return NULL;\n")
    f.write("    }\n")
    f.write("    return &syscall_table[syscall_number];\n")
    f.write("}\n")

print("C file 'syscall_table.c' generated successfully.")
