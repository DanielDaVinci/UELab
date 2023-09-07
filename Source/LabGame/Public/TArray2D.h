// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

/**
 * 
 */
template<typename ElementType>
class TArray2D
{
private:

	int32 sizeR = 0;
    int32 sizeC = 0;
    TArray<ElementType> innerArray;

public:

	void Init(const ElementType& Element, int32 RowSize, int32 ColumnSize)
    {
        sizeR = RowSize;
        sizeC = ColumnSize;

        innerArray.Init(Element, RowSize * ColumnSize);
    }

	int32 GetRowSize() { return sizeR; }
    int32 GetColumnSize() { return sizeC; }

	ElementType& Get(int32 RowIndex, int32 ColumnIndex) 
    { 
        return innerArray[RowIndex * sizeC + ColumnIndex]; 
    }

    void Set(int32 RowIndex, int32 ColumnIndex, const ElementType& Element)
    {
        innerArray[RowIndex * sizeC + ColumnIndex] = Element;
    }

};
