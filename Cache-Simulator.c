import java.io.*;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Scanner;

class Cache{
    String tag;
    int time;
    boolean valid;
    String data;

}


public class Main {
    static int setIndexL2;
    static int associativityL2;
    static int blockSizeL2;
    static int tagSizeL2;
    static int arg3;
    static int arg4;
    static int arg5;
    static int arg0;
    static int arg1;
    static int arg2;
    static int setIndexL1;
    static int associativityL1;
    static int blockSizeL1;
    static int addressBitsL1;
    static int tagSizeL1;
    static int time;
    static LinkedList<String[]> arrayLL;
    static LinkedList<Cache> CacheL2;
    static LinkedList<Cache> CacheL1I;
    static LinkedList<Cache> CacheL1D;

    public static void main(String[] args) throws IOException {


        time = 1;
        arg0 = 2;
        arg1 = 2;
        arg2 = 4;
        setIndexL1 = arg0;
        associativityL1 = arg1;
        blockSizeL1 = arg2;
        addressBitsL1 = 32;
        tagSizeL1 = addressBitsL1 - (setIndexL1 + blockSizeL1);


        CacheL1I = new LinkedList<Cache>();
        for (int i = 0; i < Math.pow(2, setIndexL1) * associativityL1; i++) {
            Cache cacheCreated = new Cache();
            cacheCreated.tag = "";
            cacheCreated.data = "";
            cacheCreated.time = 0;
            cacheCreated.valid = false;

            CacheL1I.add(cacheCreated);
        }

        CacheL1D = new LinkedList<Cache>();
        for (int i = 0; i < Math.pow(2, setIndexL1) * associativityL1; i++) {
            Cache cacheCreated = new Cache();
            cacheCreated.tag = "";
            cacheCreated.data = "";
            cacheCreated.time = 0;
            cacheCreated.valid = false;

            CacheL1D.add(cacheCreated);
        }


        //set index
        arg3 = 2;
        //associativity
        arg4 = 2;
        //blocksize
        arg5 = 4;

        setIndexL2 = arg3;
        associativityL2 = arg4;
        blockSizeL2 = arg5;

        int addressBitsL2 = 32;

        tagSizeL2 = addressBitsL2 - (setIndexL2 + blockSizeL2);


        CacheL2 = new LinkedList<Cache>();
        for (int i = 0; i < Math.pow(2, setIndexL2) * associativityL2; i++) {
            Cache cacheCreated = new Cache();
            cacheCreated.tag = "";
            cacheCreated.data = "";
            cacheCreated.time = 0;
            cacheCreated.valid = false;

            CacheL2.add(cacheCreated);
        }


        arrayLL = new LinkedList<String[]>();


        String str = "";
        File file = new File("ram.txt");

        int index = 0, totalCount = 0;
        String strArr[] = new String[1000];
        try (FileReader fr = new FileReader(file)) {
            int content;
            while ((content = fr.read()) != -1) {

                char ch = (char) content;
                if (ch == ' ') {
                    continue;
                }
                str += ch;
                if (str.length() == 16) {
                    strArr[index] = str;

                    //func(arrayLL,str,count);
                    str = "";
                    index++;

                    if (index % 1000 == 0) {
                        if (totalCount == 2000) {
                        }
                        arrayLL.add(strArr);
                        strArr = new String[1000];
                        totalCount += index;
                        index = 0;
                    }


                }


            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        arrayLL.add(strArr);

        System.out.println("count : " + (totalCount + index));


        loadToL1D("0", 4);
        loadToL1I("0", 4);

        try {
            File myObj = new File("test_medium.trace");
            Scanner myReader = new Scanner(myObj);
            while (myReader.hasNextLine()) {
                String data = myReader.nextLine();

                //addres size data
                System.out.println("");
                System.out.println(data);

                String input = data;
                String inputArr[] = input.split(" ");
                if (input.equals("M 00000720, 6, ba9b7df50be1")) {
                    System.out.println("here");
                }
                if (inputArr[0].trim().equals("L")) {
                    if (inputArr[1].contains(",")) {
                        int ind = inputArr[1].indexOf(",");
                        String s = inputArr[1].substring(0, ind) + inputArr[1].substring(ind + 1);
                        inputArr[1] = s;
                    }

                    loadToL1D(inputArr[1].trim(), Integer.parseInt(inputArr[2].trim()));
                } else if (inputArr[0].trim().equals("I")) {
                    if (inputArr[1].contains(",")) {
                        int ind = inputArr[1].indexOf(",");
                        String s = inputArr[1].substring(0, ind) + inputArr[1].substring(ind + 1);
                        inputArr[1] = s;
                    }

                    loadToL1I(inputArr[1].trim(), Integer.parseInt(inputArr[2].trim()));
                } else if (inputArr[0].trim().equals("S")) {
                    if (inputArr[1].contains(",")) {
                        int ind = inputArr[1].indexOf(",");
                        String s = inputArr[1].substring(0, ind) + inputArr[1].substring(ind + 1);
                        inputArr[1] = s;
                    }
                    if (inputArr[2].contains(",")) {
                        int ind = inputArr[2].indexOf(",");
                        String s = inputArr[2].substring(0, ind) + inputArr[2].substring(ind + 1);
                        inputArr[2] = s;
                    }

                    storeValue(inputArr[1].trim(), Integer.parseInt(inputArr[2].trim()), Integer.parseInt(inputArr[2].trim()) + inputArr[3].length(), inputArr[3].toUpperCase());
                } else if (inputArr[0].trim().equals("M")) {
                    if (inputArr[1].contains(",")) {
                        int ind = inputArr[1].indexOf(",");
                        String s = inputArr[1].substring(0, ind) + inputArr[1].substring(ind + 1);
                        inputArr[1] = s;
                    }
                    if (inputArr[2].contains(",")) {
                        int ind = inputArr[2].indexOf(",");
                        String s = inputArr[2].substring(0, ind) + inputArr[2].substring(ind + 1);
                        inputArr[2] = s;
                    }
                    //loadToL1D(inputArr[1].trim(), Integer.parseInt(inputArr[2].trim()) );
                    loadToL1D(inputArr[1].trim(), Integer.parseInt(inputArr[2].trim()));
                    storeValue(inputArr[1].trim(), Integer.parseInt(inputArr[2].trim()), Integer.parseInt(inputArr[2].trim()) + inputArr[3].length(), inputArr[3].toUpperCase());
                }


            }
            myReader.close();
        } catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }


        PrintWriter writer = new PrintWriter("L1D-Cache.txt", "UTF-8");

        for (int set = 0; set < Math.pow(2,setIndexL1) ; set++) {
            writer.println("Set " + set);
                for (int num = 0; num < Math.pow(2,blockSizeL1) ; num=num+8) {
                    String b = Integer.toBinaryString(num);
                    while(b.length()<blockSizeL1){
                        b = "0" + b;
                    }
                    String tagL1D = CacheL1D.get(set).tag;
                    String setL1D = "" + set / setIndexL1;
                    while(setL1D.length()<setIndexL1){
                        setL1D = "0"+setL1D;
                    }
                    String addr = tagL1D + setL1D + b;

                    int addresDec = Integer.parseInt(addr,2);
                    int numOfLL = addresDec / 1000, addrOfBlock = addresDec % 1000, addrOfArr = addrOfBlock / 8, offset = addrOfBlock % 8;
                    if (arrayLL.size() < numOfLL || arrayLL.size() == numOfLL && arrayLL.get(numOfLL).length < addrOfArr) {
                        return;
                    }
                    String correspArr = (arrayLL.get(numOfLL))[addrOfArr];

                    System.out.println(correspArr);
                    writer.println(correspArr);
                }

        }

        writer.close();


        writer = new PrintWriter("L1I-Cache.txt", "UTF-8");
        for (int set = 0; set < Math.pow(2,setIndexL1) ; set++) {
            writer.println("Set " + set);
            for (int num = 0; num < Math.pow(2,blockSizeL1) ; num=num+8) {
                String b = Integer.toBinaryString(num);
                while(b.length()<blockSizeL1){
                    b = "0" + b;
                }
                String tagL1D = CacheL1I.get(set).tag;
                String setL1D = "" + set / setIndexL1;
                while(setL1D.length()<setIndexL1){
                    setL1D = "0"+setL1D;
                }
                String addr = tagL1D + setL1D + b;

                int addresDec = Integer.parseInt(addr,2);
                int numOfLL = addresDec / 1000, addrOfBlock = addresDec % 1000, addrOfArr = addrOfBlock / 8, offset = addrOfBlock % 8;
                if (arrayLL.size() < numOfLL || arrayLL.size() == numOfLL && arrayLL.get(numOfLL).length < addrOfArr) {
                    return;
                }
                String correspArr = (arrayLL.get(numOfLL))[addrOfArr];

                System.out.println(correspArr);
                writer.println(correspArr);
            }

        }



        writer.close();

        writer = new PrintWriter("L2-Cache.txt", "UTF-8");
        for (int set = 0; set < Math.pow(2,setIndexL2) ; set++) {
            writer.println("Set " + set);
            for (int num = 0; num < Math.pow(2,blockSizeL2) ; num=num+8) {
                String b = Integer.toBinaryString(num);
                while(b.length()<blockSizeL2){
                    b = "0" + b;
                }
                String tagL2 = CacheL2.get(set).tag;
                String setL2 = "" + set / setIndexL2;
                while(setL2.length()<setIndexL2){
                    setL2 = "0"+setL2;
                }
                String addr = tagL2 + setL2 + b;

                int addresDec = Integer.parseInt(addr,2);
                int numOfLL = addresDec / 1000, addrOfBlock = addresDec % 1000, addrOfArr = addrOfBlock / 8, offset = addrOfBlock % 8;
                if (arrayLL.size() < numOfLL || arrayLL.size() == numOfLL && arrayLL.get(numOfLL).length < addrOfArr) {
                    return;
                }
                String correspArr = (arrayLL.get(numOfLL))[addrOfArr];

                System.out.println(correspArr);
                writer.println(correspArr);
            }

        }



        writer.close();
    }



    static void storeValue(String addr,int startIndex,int endIndex,String data){
        int addresDec = Integer.parseInt(addr,16);
        int numOfLL = addresDec/1000, addrOfBlock = addresDec%1000,addrOfArr=addrOfBlock/8,offset=addrOfBlock%8;
        String correspArr = (arrayLL.get(numOfLL))[addrOfArr];
        if(addr.equals("00005a30")){
            System.out.println("");
        }
        String s = correspArr.substring(0,startIndex);
        s+=data;
        while (s.length()>16){
            s = s.substring(1);
        }
        if(endIndex<16){
            s+=correspArr.substring(endIndex);
        }
        (arrayLL.get(numOfLL))[addrOfArr] = s;
        String binary = Integer.toBinaryString(addresDec);
        for(int i=binary.length();i<32;i++){
            binary="0"+binary;
        }
        String binaryset = binary.substring(tagSizeL1,tagSizeL1+arg0);
        int set;
        if(binaryset.equals("")){
            set=0;
        }else{
            set = Integer.parseInt(binaryset,2);
        }

        String tag = binary.substring(0,tagSizeL1);

        searchL1D(tag,set,startIndex,endIndex,data,offset);
        searchL1I(tag,set,startIndex,endIndex,data,offset);

        String binaryset2 = binary.substring(tagSizeL2,tagSizeL2+arg3);
        int set2;
        if(binaryset2.equals("")){
            set2=0;
        }else{
            set2 = Integer.parseInt(binaryset2,2);
        }
        String tag2 = binary.substring(0,tagSizeL2);
        searchL2(tag2,set2,startIndex,endIndex,data,offset);
    }

    static void searchL2(String tag,int set,int startIndex,int endIndex,String data,int offset){
        Cache newCache = new Cache();
        for(int i=set*associativityL2;i<set*associativityL2+associativityL2;i++){
            if(CacheL2.get(i).valid && CacheL2.get(i).tag.equals(tag)){
                String correspArr = CacheL2.get(i).data;
                int cacheTime = CacheL2.get(i).time;
                String s = correspArr.substring(0,startIndex);
                s+=data;
                while (s.length()>16){
                    s = s.substring(1);
                }
                if(endIndex<16){
                    s+=correspArr.substring(endIndex);
                }
                while (s.length()>16){
                    s = s.substring(1);
                }

                newCache.data=s;
                newCache.valid=true;
                newCache.tag=tag;
                newCache.time=cacheTime;

                CacheL2.set(i,newCache);
                return;
            }
        }

    }


    static void searchL1I(String tag,int set,int startIndex,int endIndex,String data,int offset){
        Cache newCache = new Cache();
        for(int i=set*associativityL1;i<set*associativityL1+associativityL1;i++){
            if(CacheL1I.get(i).valid && CacheL1I.get(i).tag.equals(tag)){
                String correspArr = CacheL1I.get(i).data;
                int cacheTime = CacheL1I.get(i).time;
                String s = correspArr.substring(0,startIndex);
                s+=data;
                while (s.length()>16){
                    s = s.substring(1);
                }
                if(endIndex<16){
                    s+=correspArr.substring(endIndex);
                }
                while (s.length()>16){
                    s = s.substring(1);
                }
                newCache.data=s;
                newCache.valid=true;
                newCache.tag=tag;
                newCache.time=cacheTime;

                CacheL1I.set(i,newCache);
                return;
            }
        }

    }


    static void searchL1D(String tag,int set,int startIndex,int endIndex,String data,int offset){
        Cache newCache = new Cache();
        for(int i=set*associativityL1;i<set*associativityL1+associativityL1;i++){
            if(CacheL1D.get(i).valid && CacheL1D.get(i).tag.equals(tag)){
                String correspArr = CacheL1D.get(i).data;
                int cacheTime = CacheL1D.get(i).time;
                String s = correspArr.substring(0,startIndex);
                s+=data;
                while (s.length()>16){
                    s = s.substring(1);
                }
                if(endIndex<16){
                    s+=correspArr.substring(endIndex);
                }
                while (s.length()>16){
                    s = s.substring(1);
                }
                newCache.data=s;
                newCache.valid=true;
                newCache.tag=tag;
                newCache.time=cacheTime;

                CacheL1D.set(i,newCache);
                return;
            }
        }

    }


    static void loadToL1D(String addr, int num){
        int addresDec = Integer.parseInt(addr,16);
        int numOfLL = addresDec/1000, addrOfBlock = addresDec%1000,addrOfArr=addrOfBlock/8,offset=addrOfBlock%8;
        if(arrayLL.size()<numOfLL || arrayLL.size()==numOfLL && arrayLL.get(numOfLL).length<addrOfArr){
            return;
        }
        String correspArr = (arrayLL.get(numOfLL))[addrOfArr];
        if(addresDec%8+num > 8){
            String correspArr2 = (arrayLL.get(numOfLL))[addrOfArr+1];
            correspArr2 = correspArr2.substring(0,(addresDec%8+num)%8*2);
            correspArr = correspArr+correspArr2;
            correspArr = correspArr.substring(addresDec%8*2);
            (arrayLL.get(numOfLL))[addrOfArr] = correspArr;
        }
        String binary = Integer.toBinaryString(addresDec);
        for(int i=binary.length();i<32;i++){
            binary="0"+binary;
        }
        String binaryset = binary.substring(tagSizeL1,tagSizeL1+arg0);
        int set;
        if(binaryset.equals("")){
            set=0;
        }else{
            set = Integer.parseInt(binaryset,2);
        }
        String tagL1D = binary.substring(0,tagSizeL1);
        loadToL2(addr,num);
        loadL1DCache(correspArr,tagL1D,set);


    }

    static void loadL1DCache(String data,String tag,int set){
        Cache newCache = new Cache();
        boolean iff=true;
        for(int i=set*associativityL1;i<set*associativityL1+associativityL1;i++){
            if(CacheL1D.get(i).valid && CacheL1D.get(i).tag.equals(tag)){
                System.out.println(" L1D hit");
                System.out.println("Place in L1D set "+ (set+(i-set*associativityL1)) + " L1D");
                iff=false;
                return;
            }

        }

        if(iff){
            for(int i=set*associativityL1;i<set*associativityL1+associativityL1;i++){
                if(CacheL1D.get(i).valid==false){
                    System.out.println(" L1D miss");
                    newCache.valid=true;
                    newCache.time=time++;
                    newCache.data=data;
                    newCache.tag=tag;

                    System.out.println("Place in L1D set "+ (set+(i-set*associativityL1)) + " L1D");
                    CacheL1D.set(i,newCache);
                    return;
                }
            }
        }



        //int min = minHeapL1D.poll();
        int min=CacheL1D.get(set*associativityL1).time;
        for(int i=set*associativityL1;i<set*associativityL1+associativityL1;i++){
            if(CacheL1D.get(i).time < min){
                min = CacheL1D.get(i).time;
            }
        }



        for(int i=set*associativityL1;i<set*associativityL1+associativityL1;i++){
            if(CacheL1D.get(i).time==min){
                newCache.time=time++;
                newCache.valid=true;
                newCache.data=data;
                newCache.tag=tag;

                System.out.println(" L1D miss");
                System.out.println("Place in L1D set "+ (set+(i-set*associativityL1)) + " L1D");
                //System.out.print(" L1D eviction");
                CacheL1D.set(i,newCache);
                break;
            }
        }


    }






    static void loadToL1I(String addr, int num){
        int addresDec = Integer.parseInt(addr,16);
        int numOfLL = addresDec/1000, addrOfBlock = addresDec%1000,addrOfArr=addrOfBlock/8,offset=addrOfBlock%8;
        if(arrayLL.size()<numOfLL || arrayLL.size()==numOfLL && arrayLL.get(numOfLL).length<addrOfArr){
            return;
        }
        String correspArr = (arrayLL.get(numOfLL))[addrOfArr];
        if(addresDec%8+num > 8){
            String correspArr2 = (arrayLL.get(numOfLL))[addrOfArr+1];
            correspArr2 = correspArr2.substring(0,(addresDec%8+num)%8*2);
            correspArr = correspArr+correspArr2;
            correspArr = correspArr.substring(addresDec%8*2);
            (arrayLL.get(numOfLL))[addrOfArr] = correspArr;
        }
        String binary = Integer.toBinaryString(addresDec);
        for(int i=binary.length();i<32;i++){
            binary="0"+binary;
        }
        String binaryset = binary.substring(tagSizeL1,tagSizeL1+arg0);
        int set;
        if(binaryset.equals("")){
            set=0;
        }else{
            set = Integer.parseInt(binaryset,2);
        }
        String tagL1I = binary.substring(0,tagSizeL1);
        loadToL2(addr,num);
        loadL1ICache(correspArr,tagL1I,set);

    }


    static void loadL1ICache(String data,String tag,int set){
        Cache newCache = new Cache();
        boolean iff=true;
        for(int i=set*associativityL1;i<set*associativityL1+associativityL1;i++){
            if(CacheL1I.get(i).valid && CacheL1I.get(i).tag.equals(tag)){
                System.out.println(" L1I hit");
                System.out.println("Place in L1I, set "+ (set+(i-set*associativityL1)) + " L1I");
                iff=false;
                return;
            }
        }

        if(iff){
            for(int i=set*associativityL1;i<set*associativityL1+associativityL1;i++){
                if(CacheL1I.get(i).valid==false){
                    System.out.println(" L1I miss");
                    newCache.valid=true;
                    newCache.time=time++;
                    newCache.data=data;
                    newCache.tag=tag;
                    System.out.println("Place in L1I set "+(set+(i-set*associativityL1)) + " L1I");
                    CacheL1I.set(i,newCache);
                    iff=false;
                    return;
                }
            }
        }



        if(iff){
            //int min = minHeapL1I.poll();
            int min=CacheL1I.get(set*associativityL1).time;
            for(int i=set*associativityL1;i<set*associativityL1+associativityL1;i++){
                if(CacheL1I.get(i).time < min){
                    min = CacheL1I.get(i).time;
                }
            }
            for(int i=set*associativityL1;i<set*associativityL1+associativityL1;i++){
                if(CacheL1I.get(i).time==min){
                    newCache.time=time++;
                    newCache.valid=true;
                    newCache.data=data;
                    newCache.tag=tag;

                    System.out.println(" L1I miss");
                    System.out.println("Place in L1I, set "+ (set+(i-set*associativityL1)) + " L1I");
                    //System.out.print(" L1I eviction");
                    CacheL1I.set(i,newCache);
                    break;
                }
            }
        }





    }


    static void loadToL2(String addr,int num){
        //arrayLL ram.txt
        //cacheL1 data cache
        int addresDec = Integer.parseInt(addr,16);
        int numOfLL = addresDec/1000, addrOfBlock = addresDec%1000,addrOfArr=addrOfBlock/8,offset=addrOfBlock%8;
        if(arrayLL.size()<numOfLL || arrayLL.size()==numOfLL && arrayLL.get(numOfLL).length<addrOfArr){
            return;
        }

        if(addr.equals("000000c0")){
            System.out.println("here");
        }
        String correspArr = (arrayLL.get(numOfLL))[addrOfArr];
        if(addresDec%8+num > 8){
            String correspArr2 = (arrayLL.get(numOfLL))[addrOfArr+1];
            correspArr2 = correspArr2.substring(0,(addresDec%8+num)%8*2);
            correspArr = correspArr+correspArr2;
            correspArr = correspArr.substring(addresDec%8*2);
            (arrayLL.get(numOfLL))[addrOfArr] = correspArr;
        }
        String binary = Integer.toBinaryString(addresDec);
        for(int i=binary.length();i<32;i++){
            binary="0"+binary;
        }
        String binaryset = binary.substring(tagSizeL2,tagSizeL2+arg3);
        int set = Integer.parseInt(binaryset,2);
        String tagL2 = binary.substring(0,tagSizeL2);
        loadL2Cache(correspArr,tagL2,set);



        //loadL2Cache(cacheL2,);



    }



    static void loadL2Cache(String data,String tag,int set){
        Cache newCache = new Cache();
        boolean iff = true;
        for(int i=set*associativityL2;i<set*associativityL2+associativityL2;i++){
            if(CacheL2.get(i).valid && CacheL2.get(i).tag.equals(tag) ){
                System.out.println(" L2 hit");
                System.out.println("Place in L2 set "+ (set+(i-set*associativityL2)) + " L2");
                iff=false;
                break;
            }
        }
        if(iff){
            for(int i=set*associativityL2;i<set*associativityL2+associativityL2;i++){
                if(CacheL2.get(i).valid==false){
                    System.out.println(" L2 miss");
                    System.out.println("Place in L2 set "+(set+(i-set*associativityL2)) + " L2");
                    newCache.valid=true;
                    newCache.time=time;
                    newCache.data=data;
                    newCache.tag=tag;
                    iff=false;
                    CacheL2.set(i,newCache);

                    break;
                }
            }
        }


        if(iff){
            //int min = minHeapL2.poll();
            int min=CacheL2.get(set*associativityL1).time;
            for(int i=set*associativityL1;i<set*associativityL1+associativityL1;i++){
                if(CacheL2.get(i).time < min){
                    min = CacheL2.get(i).time;
                }
            }
            for(int i=set*associativityL2;i<set*associativityL2+associativityL2;i++){
                if(CacheL2.get(i).time==min){
                    newCache.time=time;
                    newCache.valid=true;
                    newCache.data=data;
                    newCache.tag=tag;

                    System.out.println(" L2 miss");
                    System.out.println("Place in L2 set "+ (set+(i-set*associativityL2)) + " L2");
                    //System.out.print(" L2 eviction");
                    CacheL2.set(i,newCache);
                    break;
                }
            }
        }






    }


    static void func(String str,int count){
        int num = count/1000;
        String intArray[];

        for(int i=0; i<num ;i++) {
            arrayLL.get(num);

        }



    }








}