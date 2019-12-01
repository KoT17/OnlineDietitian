import { Component, OnInit } from '@angular/core';
import {FormControl} from '@angular/forms';
import {Observable} from 'rxjs';
import {map, startWith, take} from 'rxjs/operators';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'app-services',
  templateUrl: './services.component.html',
  styleUrls: ['./services.component.css']
})
export class ServicesComponent implements OnInit {
options: string[] = [];
  filteredOptions: Observable<string[]>;
  myControl = new FormControl();
  selection: string = '';
  food;
  constructor(private http: HttpClient) {

  }

  ngOnInit() {
    // *************** INSERT URL HERE ****************
    this.http.get("http://localhost:3000/food").pipe(take(1)).subscribe(food => {
        this.food = Object.values(food);
        Object.values(food).forEach(item => {
          this.options.push(item.name);
        });
        this.filteredOptions = this.myControl.valueChanges
          .pipe(
            startWith(''),
            map(value => this._filter(value))
          );
    });
  }

  private _filter(value: string): string[] {
    const filterValue = value.toLowerCase();

    return this.options.filter(option => option.toLowerCase().includes(filterValue));
  }

  doSomething(selection) {
    this.food.forEach(item => {
      if(item.name == selection) {
        this.selection = item;
      }
    });
  }
}
