import copy
import logging

# logging.basicConfig(level=logging.DEBUG)

# define current and goal positions
current = dict(ziege="start", kohlkopf="start", wolf="start", fahrer="start")
goal = dict(ziege="pil", kohlkopf="pil", wolf="pil", fahrer="pil")


def toggle_location(node, index):
    if node[index] == "pil":
        node[index] = "start"
    else:
        node[index] = "pil"


def move_z(node):
    toggle_location(node, "ziege")
    toggle_location(node, "fahrer")


def move_k(node):
    toggle_location(node, "kohlkopf")
    toggle_location(node, "fahrer")


def move_w(node):
    toggle_location(node, "wolf")
    toggle_location(node, "fahrer")


def move_f(node):
    toggle_location(node, "fahrer")


adj_list = [move_z, move_k, move_w, move_f]


def check(node):
    if (node["ziege"] == node["wolf"] != node["fahrer"]
            or node["ziege"] == node["kohlkopf"] != node["fahrer"]):
        return False
    return True


def deep_search(node, discovered, depth):
    if node == goal:
        return discovered
    if depth > 0:
        for adj in adj_list:
            neighbor = copy.deepcopy(node)
            adj(neighbor)
            logging.debug(str(depth) + str(neighbor) + str(len(discovered)))
            if neighbor in discovered or not check(neighbor):
                logging.debug("next")
                continue
            else:
                new_discovered = copy.deepcopy(discovered)
                new_discovered.append(neighbor)
                return_value = deep_search(neighbor, new_discovered, depth - 1)
                if return_value is not None:
                    return return_value
    return None


def deep_search_loop(start, depth):
    return_value = deep_search(start, [start], depth)
    if return_value is not None:
        return return_value
    logging.debug("")
    logging.debug("search on depth: " + str(depth + 1))
    return deep_search_loop(start, depth + 1)


def print_way(dict_list):
    print("%-10s %-10s %-10s %-10s"
          % ("ziege", "kohlkopf", "wolf", "fahrer"))
    for d in dict_list:
        print("%-10s %-10s %-10s %-10s"
                % (d["ziege"], d["kohlkopf"], d["wolf"], d["fahrer"]))


def main():
    result = deep_search_loop(current, 1)
    if result is not None:
        print_way(result)
    else:
        print("nothing found")


if __name__ == '__main__':
    main()
