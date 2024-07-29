# 邏輯閘模擬器

一個簡單的邏輯閘模擬器，用於執行 AND, OR, NOT 操作，並且支持一個未賦值狀態。

## 目錄

- [簡介](#簡介)
- [安裝](#安裝)
- [使用方法](#使用方法)
- [範例](#範例)

## 簡介

這個項目是一個基於 C++ 的邏輯閘模擬器，支持 AND, OR, NOT 操作。值的範圍包括 0、1 和一個表示未賦值狀態的特殊值。

## 安裝

如果使用Linux可以快速執行：

```bash
sh go.sh
```
或自行編譯 main.cpp LogicGate.cpp  
#注意，該程式碼要求c++11以上

## 使用方法

下面是一個關鍵代碼，展示如何根據輸入iPins 判斷最終輸出oPins：

```main.cpp
#LogicCircuit Class
private:
    int inputPinsCount;
    int gatesCount;
    std::vector<std::shared_ptr<LogicGate>> gates;
    std::vector<std::shared_ptr<LogicGate>> _iPins;
public:
    std::vector<int8_t> simuulate(std::vector<int8_t> iPins)
    {
        // 設定iPins;
        for(int i=0; i<inputPinsCount; i++)
        {
            _iPins[i]->addInputPin(iPins[i]);
        }

        bool undone = true;
        while(undone){
            undone = false;
            for(int i=0; i<gatesCount; i++)
            {
                if(gates[i]->getOutput()==UNINITIALIZED){
                    undone=true;
                    gates[i]->compute(); //根據gatetype做計算
                }
            }
        }

        //藉由shar_ptr被ref次數做判斷，
        //如果為輸出，只能被參考2次，為 gates vector 及 本身的gate class所ref
        std::vector<int8_t> opins;
        for(auto gate : gates){
            if(gate.use_count() == 2){
                opins.push_back(gate->getOutput());
            }
        }

        for(int i=0; i<gatesCount; i++)
        {
            gates[i]->reset();
        }
        return opins;
    }
```

## 範例
假設放入的檔案
```
3
3
1 -1 2.1 3.1 0
3 -2 0
2 2.1 -3 0
```

則執行3.真值表的操作結果如下：
```
iii|o
123|1
------+--
000|0
001|0
010|0
011|0
100|1
101|1
110|0
111|0
```
