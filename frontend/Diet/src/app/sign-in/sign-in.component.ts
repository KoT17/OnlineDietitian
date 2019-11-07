import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { MatDialog } from '@angular/material';
import { SignInService } from '../sign-in.service';

@Component({
  selector: 'app-sign-in',
  templateUrl: './sign-in.component.html',
  styleUrls: ['./sign-in.component.css']
})
export class SignInComponent implements OnInit {
  username: string;
  password: string;
  constructor(private signInService: SignInService, private router: Router) { }
  ngOnInit() {
  }
  login() : void {
    if(this.username == 'admin' && this.password == 'admin'){
      this.signInService.setIsLoggedIn(true);
      this.router.navigate(["authhome"]);
    } else {
      alert("Invalid username/password");
      }
    }
   register() : void {
     this.router.navigate(["reg"]);
   }
 }

