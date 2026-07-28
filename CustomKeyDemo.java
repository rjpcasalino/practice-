import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

// Modern Java 14+ Record automatically generates proper hashCode() and equals()!
record CharacterKey(char symbol, String encoding) {}

public class CustomKeyDemo {
    public static void main(String[] args) {
        Map<CharacterKey, String> keyMap = new HashMap<>();

        CharacterKey k1 = new CharacterKey('Æ', "UTF-8");
        keyMap.put(k1, "Latin Capital Letter AE");

        // Lookup using a completely new object instance with matching values
        CharacterKey searchKey = new CharacterKey('Æ', "UTF-8");
        
        // This works because Records implement hashCode() and equals() value-based equality automatically
        System.out.println("Result: " + keyMap.get(searchKey));
    }
}
