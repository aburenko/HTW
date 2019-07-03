import java.util.LinkedList;

public class BayesianNetwork {
    private LinkedList<NodeProbability> nodes;

    public BayesianNetwork () {
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
        bn.addNode("lightning", "", "t:0.01 f:0.99");

        bn.addNode("alarm", "earthquake robbery lightning",
                "tttf:0.95 fttf:0.05 ttff:0.29 ftff:0.71 tftf:0.94 fftf:0.06 tfff:0.001 ffff:0.999" +
                           " tttt:0.95 fttt:0.05 ttft:0.29 ftft:0.71 tftt:0.94 fftt:0.06 tfft:0.05 ffft:0.95" );

        bn.addNode("john","alarm","tt:0.9 ft:0.1 tf:0.05 ff:0.95");
        bn.addNode("mary","alarm","tt:0.7 ft:0.3 tf:0.01 ff:0.99");

        return bn;
    }
}
