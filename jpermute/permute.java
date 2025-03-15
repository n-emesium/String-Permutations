import java.util.ArrayList;
public class permute {
    public static void main(String[] args) {
        for (String s : args) {
            ArrayList<String> permuted = new ArrayList<String>();
            px(s, permuted, new ArrayList<Character>());
            System.out.println(permuted);
        }
    }

    public static void px(String s, ArrayList<String> store, ArrayList<Character> temp) {
        if (s.length() == 0) {
            store.add(convert(temp));
            return;
        }
        for (int i = 0; i < s.length(); i++) {
            temp.add(s.charAt(i)); 
            px(s.substring(0, i) + s.substring(i + 1), store, temp);
            temp.remove(temp.size() - 1);
        }
    }


    public static String convert(ArrayList<Character> arr) {
        String s = "";
        for (int i = 0; i < arr.size(); i++) {
            s += arr.get(i);
        }
        return s;
    }
}
