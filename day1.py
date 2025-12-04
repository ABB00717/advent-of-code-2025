point = 50
res = 0

with open("input", "r") as f:
    for instr in f:
        rot = instr[0]
        number = int(instr[1:])

        if rot == "R":
            res += (point + number) // 100
            point = (point + number) % 100
        else:
            # It's so freaking hard WTF
            dist_to_zero = point if point > 0 else 100
            # Cause it's sooo hard, we cut it first to make it start
            # from 0.
            if number >= dist_to_zero:
                res += 1
                remaining = number - dist_to_zero
                res += remaining // 100
            point = (point - number) % 100

        print(instr.strip(), ": res - ", res, " new_point - ", point)

print("Final:", res)
