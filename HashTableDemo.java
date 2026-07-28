import java.util.HashMap;
import java.util.Map;

public class HashTableDemo {
    public static void main(String[] args) {
        // Use the Map interface as the type reference, and HashMap as the concrete implementation
        Map<String, Integer> entityLookup = new HashMap<>();

        // 1. Insertion (put)
        entityLookup.put("AElig", 0x00C6);
        entityLookup.put("Aacute", 0x00C1);
        entityLookup.put("Acirc", 0x00C2);
        entityLookup.put("zeta", 0x03B6);

        // 2. Retrieval (get & getOrDefault)
        String searchKey = "Acirc";
        if (entityLookup.containsKey(searchKey)) {
            System.out.printf("Found '%s' -> 0x%04X%n", searchKey, entityLookup.get(searchKey));
        }

        // Safe retrieval with a fallback default value
        int value = entityLookup.getOrDefault("omega", -1);
        System.out.println("Lookup 'omega' (missing): " + value);

        // 3. Iteration over Key-Value Pairs (Map.Entry)
        System.out.println("\n--- All Entities in Hash Table ---");
        for (Map.Entry<String, Integer> entry : entityLookup.entrySet()) {
            System.out.printf("Key: %-8s | Value: 0x%04X%n", entry.getKey(), entry.getValue());
        }

        // 4. Functional Iteration (Java 8+)
        System.out.println("\n--- Lambda Iteration ---");
        entityLookup.forEach((key, val) -> 
            System.out.printf("%s => %d%n", key, val)
        );

        // 5. Deletion
        entityLookup.remove("zeta");
        System.out.println("\nContains 'zeta' after remove? " + entityLookup.containsKey("zeta"));
    }
}
