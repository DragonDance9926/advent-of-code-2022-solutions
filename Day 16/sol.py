from collections import defaultdict
from functools import lru_cache
ddict =dict()
with open('input.txt') as f:
    for line in f:
        flines = line.split(' ')
        start = flines[1]
        f_rate = flines[4][5:-1]
        ends = [s.strip().strip(',').strip('\n') for s in flines[9:]]
        ddict[start] = [int(f_rate), ends]
@lru_cache(maxsize=None)

def maxflow(cur, opened, min_left):
    if min_left <= 0:
        return 0
    best = 0
    if cur not in opened:
        val = (min_left - 1) * ddict[cur][0]
        cur_opened = tuple(sorted(opened + (cur,)))
        for adj in ddict[cur][1]:
            if val > 0:
                best = max(best ,
                    val + maxflow(adj, cur_opened, min_left - 2))
            best = max(best,
                maxflow(adj , opened, min_left - 1))
    else:
        for(adj) in ddict[cur][1]:
            best = max(best,
                maxflow(adj, opened, min_left - 1))
    return best

print("Part 1: ",maxflow('AA', (), 30))

@lru_cache(maxsize=None)
def maxflow2(my_cur, e_curr, opened, min_left):
    if min_left <= 0:
        return 0
    best = 0
    val_my = (min_left - 1) * ddict[my_cur][0]
    val_e = (min_left - 1) * ddict[e_curr][0]
    for adj_my in ddict[my_cur][1]:
        for adj_e in ddict[e_curr][1]:
            if adj_my == adj_e:
                continue
            if adj_my not in opened and adj_e not in opened:
                best = max(best,
                    val_my + val_e + maxflow2(adj_my, adj_e, opened + (adj_my, adj_e), min_left - 2))
            elif adj_my not in opened:
                best = max(best,
                    val_my + maxflow2(adj_my, adj_e, opened + (adj_my,), min_left - 2))
            elif adj_e not in opened:
                best = max(best,
                    val_e + maxflow2(adj_my, adj_e, opened + (adj_e,), min_left - 2))
            else:
                best = max(best,
                    maxflow2(adj_my, adj_e, opened, min_left - 2))
    return best

print(maxflow2('AA','AA', (), 26))

