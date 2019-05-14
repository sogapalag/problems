

def to_snippets(addr, to="./out.conf"):
    st = "SNIPPETS_START"
    en = "SNIPPETS_END"
    try:
        with open(addr, 'r') as rf:
            with open(to, 'w+') as wf:
                flag = False
                while True:
                    line = rf.readline()
                    # ~ print(line)
                    if not flag:
                        if st not in line:
                            continue;
                        flag = True
                        wf.write("snippet ")
                        wf.write(line.split(st, 1)[1].strip() + "\n")
                    else:
                        if en in line:
                            break;
                        wf.write('\t' + line)
    except:
        print("read file not found");

def main():
    addr = "./templates/kstmp.cpp"
    to_snippets(addr)

if __name__ == "__main__":
    main()

