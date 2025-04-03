# LRU Cache

## What is LRU Cache
Please refer to https://www.youtube.com/watch?v=S6IfqDXWa10

## Advantages of C++ Implementation
1. std::list is a double linked list, so developers don't need to worry about dummy head or reinvent the wheel but can directly use std::list to implement.
2. C++ offers std::pair, so developers don't need to define Node class but can directly use std::pair to implement.
3. C++ offers choices for in-place object construction. developers can choose based on their need for memory operations.
4. C++ new standards offer concise ways of coding, e.g. std::list insert_or_assign. Developers don't need to take lines to check whether the key exists and what to do after that.

## LRU Cache of Java Implementation
Comparatively, very verbose.

```java
class Node{
	int key;
	int value;
	Node pre;
	Node nxt;
	Node(int k,int v){
		key=k;
		value=v;
		pre=null;
		nxt=null;
	}
	public void deleteSelf(){
		Node pre=this.pre;
		Node nxt=this.nxt;
		pre.nxt=nxt;
		nxt.pre=pre;
	}
	public void addAfter(Node n){
		Node pre=n;
		Node nxt=n.nxt;
		this.pre=pre;
		this.nxt=nxt;
		pre.nxt=this;
		nxt.pre=this;
	}
}

class LRUCache {

    private Node[] map;
    private int size;
    private int capacity;
    Node head;
    Node tail;
    
    public LRUCache(int capacity) {
        map=new Node[20000];
        head=new Node(-1,-1);
        tail=new Node(-1,-1);
        head.nxt=tail;
        tail.pre=head;
         this.capacity=capacity;
    }
    
    public int get(int key) {
        if(map[key]!=null){
            Node cur=map[key];
            int ret=map[key].value;
            cur.deleteSelf();
            cur.addAfter(head);
            return ret;
        }
        else
            return -1;
    }
    
    public void put(int key, int value) {
        if(map[key]!=null){
        	Node del=map[key];
        	del.deleteSelf();
        	size--;
        	map[del.key]=null;        	
        }
        if(size>0 && size==capacity){
        	Node del=tail.pre;
        	del.deleteSelf();
        	size--;
        	map[del.key]=null;
        }
        Node node=new Node(key,value);
        node.addAfter(head);
        map[key]=node;
        size++;
        
    }
}
```

