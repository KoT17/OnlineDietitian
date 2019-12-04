import { Component, OnInit } from '@angular/core';
import { FormControl } from '@angular/forms';
import { Observable } from 'rxjs';
import { map, startWith, take, catchError } from 'rxjs/operators';
import { HttpClient, HttpErrorResponse, HttpHeaders } from '@angular/common/http';
import { throwError } from 'rxjs';

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
    this.http.get('http://localhost:4201/NutritionalLookup?search=', { headers: new HttpHeaders({
      source: 'lookup',
      user: '',
      password: ''
    })}).pipe(catchError(this.handleError)).pipe(take(1)).subscribe(food => {
        this.food = Object.values(food);
        Object.values(food).forEach(item => {
          this.options.push(item.food_name);
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
      if(item.food_name == selection) {
        this.selection = item;
      }
    });
  }

  handleError(error: HttpErrorResponse) {
     alert("Couldn't retrieve food items!");
     return throwError('');
   }
}
