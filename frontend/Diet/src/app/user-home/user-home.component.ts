import { Component, OnInit } from '@angular/core';
import { SignInService } from '../sign-in.service';
import { throwError } from 'rxjs';
import { take, catchError } from 'rxjs/operators';
import { HttpClient, HttpHeaders, HttpErrorResponse } from '@angular/common/http';

@Component({
  selector: 'app-user-home',
  templateUrl: './user-home.component.html',
  styleUrls: ['./user-home.component.css']
})
export class UserHomeComponent implements OnInit {
  diets = [1,2,3,4,5,6,7]

  constructor(private signInService: SignInService, private http: HttpClient) { }

  ngOnInit() {
    this.http.get('http://localhost:4201/NutritionalLookup', { headers: new HttpHeaders({
      source: 'user_info',
      user: this.signInService.getUser().email,
      password: this.signInService.getUser().password
    })}).pipe(take(1)).pipe(catchError(this.handleError)).subscribe(res => {
      console.log(res)
    });
  }

  handleError(error: HttpErrorResponse) {
     alert("Couldn't retrieve diets!");
     return throwError('');
   }
}
