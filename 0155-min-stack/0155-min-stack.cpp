class MinStack {
    vector<int> nums;
    vector<int> min;
public:
    MinStack() {

    }

    void push(int val) {
        nums.push_back(val);
        if (min.empty() || val <= min.back()) {
            min.push_back(val);
        } else {
            min.push_back(min.back());
        }
    }
    
    void pop() {
        if (!nums.empty()) {
            nums.pop_back();
            min.pop_back();
        }
    }
    
    int top() {
        return nums.back();
    }
    
    int getMin() {
        return min.back();    
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(value);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */