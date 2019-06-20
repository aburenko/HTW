import java.util.LinkedList;

public class BayesianNetwork {
    private LinkedList<NodeProbability> nodes;

    BayesianNetwork () {
        nodes = new LinkedList<>();
    }

    public LinkedList<NodeProbability> getNodes() {
        return nodes;
    }

    public void addNode(String nodeName, String dependencies, String distribution) {
        try {
            int place = 0;
            if (!dependencies.isEmpty()) {
                // search for dependencies in List
                for (String dependency
                        : dependencies.split(" ")) {
                    int cursor = 1;
                    for (NodeProbability np : nodes) {
                        if (np.getName().equals(dependency) && cursor > place)
                            place = cursor;
                        cursor++;
                    }
                }
            }
            nodes.add(place, new NodeProbability(nodeName, dependencies, distribution));
            System.out.println("add: " + nodeName + " on: " + place);

        } catch (IllegalArgumentException e) {
            System.err.println(e.getMessage());
        }
    }

    public int getNodeNumber() {
        return this.nodes.size();
    }

    public static BayesianNetwork buildAlarmExample() {
        BayesianNetwork bn = new BayesianNetwork();
        bn.addNode("earthquake","","t:0.002 f:0.998");
        bn.addNode("robbery","","t:0.001 f:0.999");

        bn.addNode("alarm", "earthquake robbery",
                "ttt:0.95 ftt:0.05 ttf:0.94 ftf:0.06 tft:0.29 fft:0.71 tff:0.001 fff:0.999");

        bn.addNode("john","alarm","tt:0.9 ft:0.1 tf:0.05 ff:0.95");
        bn.addNode("mary","alarm","tt:0.7 ft:0.3 tf:0.01 ff:0.99");

        return bn;
    }
}
