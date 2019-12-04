import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { HttpClient, HttpHeaders, HttpErrorResponse } from '@angular/common/http';
import { SignInService } from '../sign-in.service';
import { throwError } from 'rxjs';
import { take, catchError } from 'rxjs/operators';

@Component({
  selector: 'app-pickdiet',
  templateUrl: './pickdiet.component.html',
  styleUrls: ['./pickdiet.component.css']
})
export class PickdietComponent implements OnInit {
  options;
  constructor(private signInService: SignInService, private http: HttpClient, private router: Router) {

  }

  ngOnInit() {
    this.http.get('http://localhost:4201/NutritionalLookup', { headers: new HttpHeaders({
      source: 'diet_choice',
      user: this.signInService.getUser().email,
      password: this.signInService.getUser().password
    })}).pipe(take(1)).pipe(catchError(this.handleError)).subscribe(res => {
      console.log(res)
      this.options = res;
      this.options.firstDiet.dietary_restrictions = this.convertDiet(this.options.firstDiet.dietary_restrictions)
      this.options.secondDiet.dietary_restrictions = this.convertDiet(this.options.secondDiet.dietary_restrictions)
    });
  }

  select(option) {
    if(option == 1) {
      this.http.post("http://localhost:4201/NutritionalLookup", {} , { headers: new HttpHeaders({
        source: "selection",
        user: this.signInService.getUser().email,
        password: this.signInService.getUser().password,
        diet: this.options.firstDiet.DietName.toString()
      })}).pipe(take(1)).pipe(catchError(this.handleErrorPost)).subscribe(res => {
        this.router.navigateByUrl('/authhome');
      });
    } else {
      this.http.post("http://localhost:4201/NutritionalLookup", {} , { headers: new HttpHeaders({
        source: "selection",
        user: this.signInService.getUser().email,
        email: this.signInService.getUser().email,
        password: this.signInService.getUser().password,
        diet: this.options.secondDiet.DietName.toString()
      })}).pipe(take(1)).pipe(catchError(this.handleErrorPost)).subscribe(res => {
        this.router.navigateByUrl('/authhome');
      });
    }
  }

  handleError(error: HttpErrorResponse) {
     alert("Couldn't retrieve diet selections!");
     return throwError('');
   }

   handleErrorPost(error: HttpErrorResponse) {
     alert("Couldn't post diet selection!");
     return throwError('');
   }

   convertDiet(diet): string {
     let number: string;
     switch(diet) {
       case 0:
         number = "None";
         break;
       case 1:
         number = "Vegan";
         break;
       case 2:
         number = "Vegetarian";
         break;
       case 3:
         number = "Gluten Free";
         break;
       default:
         break;
     }
     return number;
   }
}
