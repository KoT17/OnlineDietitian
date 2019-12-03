import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { MatDialog } from '@angular/material';
import { SignInService } from '../sign-in.service';
import { HttpClient, HttpHeaders, HttpErrorResponse } from '@angular/common/http';
import { take, catchError } from 'rxjs/operators';
import { throwError } from 'rxjs';

@Component({
  selector: 'app-sign-in',
  templateUrl: './sign-in.component.html',
  styleUrls: ['./sign-in.component.css']
})
export class SignInComponent implements OnInit {
  username: string;
  password: string;
  constructor(private http: HttpClient, private signInService: SignInService, private router: Router) { }
  ngOnInit() {
  }
  login() : void {
    this.http.post('http://localhost:4201/NutritionalLookup', {}, {headers: new HttpHeaders({
        source: 'login',
        email: this.username,
        password: this.password
      })
    }).pipe(take(1)).pipe(catchError(this.handleError)).subscribe(res => {
      this.signInService.setUser(res);
      this.signInService.setIsLoggedIn(true);
      this.router.navigate(["authhome"]);
    })
  }
   register() : void {
     this.router.navigate(["reg"]);
   }

   handleError(error: HttpErrorResponse) {
     alert("Invalid username/password");
     return throwError('');
   }
 }

